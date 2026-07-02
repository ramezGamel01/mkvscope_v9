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

void build_track_index(Movie& movie){
 std::set<uint32_t> seen;
 for(auto& t:movie.segment.tracks){
 if(!seen.insert(t.number).second) movie.segment.warnings.push_back("duplicate-track:"+std::to_string(t.number));
 }
 }

void build_frame_index(Movie& movie){
 for(auto& t: movie.segment.tracks){
 std::stable_sort(t.frames.begin(), t.frames.end(), [](const BlockFrame&a,const BlockFrame&b){
 return a.absolute_time<b.absolute_time; }
);
 for(size_t i=1;i<t.frames.size();++i){
 if(t.frames[i].absolute_time<t.frames[i-1].absolute_time) movie.segment.warnings.push_back("nonmonotonic");
 }
 }
 }

}
