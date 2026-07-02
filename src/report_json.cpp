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

void write_json_report(std::ostream& os,const Movie& m){
 os<<"{\"tracks\":[";
 bool first=true;
 for(const auto& t:m.segment.tracks){
 if(!first) os<<",";
 first=false;
 std::string codec=t.entries.empty()?"none":json_escape(t.entries[0].codec_id);
 std::string tmp="{\"n\":"+std::to_string(t.number)+",\"codec\":\""+codec+"\",\"frames\":"+std::to_string(t.frames.size())+"}";
 os.write(tmp.data(), tmp.size());
 }
 os<<"],\"tags\":"<<m.segment.tag_index.size()<<"}";
 }

std::string movie_json_report(const Movie& m){
 std::ostringstream os;
 write_json_report(os,m);
 return os.str();
 }

}
