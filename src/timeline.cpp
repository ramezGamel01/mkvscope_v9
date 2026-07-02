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

void apply_timecode_scale(Movie& movie){
 uint64_t scale=movie.segment.info.timecode_scale?movie.segment.info.timecode_scale:1000000;
 for(auto& tr:movie.segment.tracks) for(auto& f:tr.frames) f.absolute_time*=scale/1000000;
 for(auto& c:movie.segment.clusters) for(auto& b:c.blocks) b.absolute_time*=scale/1000000;
 }

void materialize_timeline(Movie& movie){
 std::map<uint32_t,Track*> tracks;
 for(auto& t:movie.segment.tracks) tracks[t.number]=&t;
 for(auto& c:movie.segment.clusters){
 for(auto& b:c.blocks){
 auto it=tracks.find(b.track);
 if(it!=tracks.end()){
 b.source_cluster=c.file_position;
 it->second->frames.push_back(b);
 }
 }
 }
 apply_timecode_scale(movie);
 }

}
