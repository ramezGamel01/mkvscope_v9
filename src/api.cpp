#include "mkvscope/api.hpp"
#include "mkvscope/ids.hpp"
#include "mkvscope/vint.hpp"
#include "mkvscope/reader.hpp"
#include "mkvscope/schema.hpp"
#include "mkvscope/numeric.hpp"
#include "mkvscope/text.hpp"
#include "mkvscope/track_decoder.hpp"
#include "mkvscope/cluster_decoder.hpp"
#include "mkvscope/block_decoder.hpp"
#include "mkvscope/lacing.hpp"
#include "mkvscope/cue_decoder.hpp"
#include "mkvscope/seek_decoder.hpp"
#include "mkvscope/tag_decoder.hpp"
#include "mkvscope/chapter_decoder.hpp"
#include "mkvscope/attachment_decoder.hpp"
#include "mkvscope/codec_private.hpp"
#include "mkvscope/avc.hpp"
#include "mkvscope/opus.hpp"
#include "mkvscope/vp9.hpp"
#include "mkvscope/segment_builder.hpp"
#include "mkvscope/resolver.hpp"
#include "mkvscope/normalizer.hpp"
#include "mkvscope/timeline.hpp"
#include "mkvscope/index.hpp"
#include "mkvscope/scoring.hpp"
#include "mkvscope/report_text.hpp"
#include "mkvscope/report_json.hpp"
#include "mkvscope/report_table.hpp"
#include "mkvscope/passes.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <unordered_map>

namespace mkv {

void analyze_movie(Movie& movie){
 materialize_timeline(movie);
 score_movie(movie);
 resolve_segment(movie);
 normalize_movie(movie);
 build_track_index(movie);
 build_frame_index(movie);
 build_tag_index(movie);
 probe_attachments(movie);
 run_deep_validation(movie);
 }

InspectResult inspect_bytes(const uint8_t* data,size_t size,InspectMode mode){
 Diagnostics diag;
 ByteView v(data,size);
 Document doc=parse_ebml(v,diag);
 Movie m=build_movie(doc);
 m.diagnostics=std::move(diag);
 m.fingerprint=fnv1a(v);
 analyze_movie(m);
 InspectResult r;
 r.ok=true;
 if(mode==InspectMode::Json) r.report=movie_json_report(m);
 else if(mode==InspectMode::Table) r.report=movie_table_report(m);
 else if(mode==InspectMode::Full) r.report=movie_text_report(m)+movie_json_report(m)+movie_table_report(m);
 else r.report=movie_text_report(m);
 r.movie=std::move(m);
 return r;
 }

InspectResult inspect_file(const std::string& path,InspectMode mode){
 std::ifstream f(path,std::ios::binary);
 std::vector<uint8_t> b((std::istreambuf_iterator<char>(f)),{
});
 return inspect_bytes(b.data(),b.size(),mode);
 }

}
