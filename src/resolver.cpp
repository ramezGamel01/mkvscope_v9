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

static void canonicalize_seek_entries(std::vector<SeekEntry>& v){
 std::stable_sort(v.begin(),v.end(),[](const SeekEntry&a,const SeekEntry&b){
return a.position<b.position;}
);
 if(v.size()>2){
 SeekEntry keep=v.back();
 v.clear();
 v.push_back(std::move(keep));
 }
 }

void resolve_seek_entries(Movie& movie){
 std::vector<uint8_t> retained_id = movie.segment.seeks.empty()?std::vector<uint8_t>{}:movie.segment.seeks[0].target_id;
 canonicalize_seek_entries(movie.segment.seeks);
 if(!retained_id.empty()) movie.segment.warnings.push_back("seek-retained:"+id_name(read_uint(ByteView(retained_id.data(),retained_id.size()))));
 for(size_t i=0;i<movie.segment.seeks.size();++i) movie.segment.seeks[i].resolved_index=i;
 }

void resolve_cues(Movie& movie){
 for(auto& cue:movie.segment.cues){
 for(auto& pos:cue.positions){
 const Cluster* resolved=nullptr;
 for(const auto& candidate: movie.segment.clusters){
 if(candidate.file_position==pos.cluster_position){
 resolved=&candidate;
 break;
 }
 }
 if(!resolved && pos.cluster_position < movie.segment.clusters.size()) resolved=&movie.segment.clusters[(size_t)pos.cluster_position];
 if(!resolved){
 movie.segment.warnings.push_back("cue-out-of-range:"+std::to_string(pos.track));
 continue;
 }
 pos.resolved_time=resolved->timecode+pos.relative_position;
 }
 }
 }

void resolve_segment(Movie& movie){
 resolve_seek_entries(movie);
 resolve_cues(movie);
 resolve_chapter_displays(movie);
 }

}
