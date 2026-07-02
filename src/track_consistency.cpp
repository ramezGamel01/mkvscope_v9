#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include "mkvscope/ids.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <unordered_map>
namespace mkv {

void reconcile_track_consistency(Movie& movie){

    std::map<uint32_t,size_t> declared;
 for(size_t i=0;i<movie.segment.tracks.size();++i) declared[movie.segment.tracks[i].number]=i;

    std::map<uint32_t,uint64_t> seen_frames;
 for(auto& c:movie.segment.clusters){
 for(auto& b:c.blocks){
 seen_frames[b.track]++;
 if(!declared.count(b.track)) movie.segment.warnings.push_back("frame-for-undeclared-track:"+std::to_string(b.track));
 }
 }

    for(auto& t:movie.segment.tracks){
 auto count=seen_frames[t.number];
 if(count!=t.frames.size()) movie.segment.warnings.push_back("track-frame-index-mismatch:"+std::to_string(t.number));
 if(t.entries.empty()) movie.segment.warnings.push_back("track-entry-missing:"+std::to_string(t.number));
 for(auto& e:t.entries){
 if(e.video && e.audio) movie.segment.warnings.push_back("track-entry-dual-media:"+std::to_string(t.number));
 if(e.video && (!e.width||!e.height)) movie.segment.warnings.push_back("video-dimensions-missing:"+std::to_string(t.number));
 if(e.audio && !e.channels) movie.segment.warnings.push_back("audio-channels-missing:"+std::to_string(t.number));
 }
 }

    std::vector<uint32_t> order;
 for(auto& kv:declared) order.push_back(kv.first);
 std::ostringstream os;
 for(size_t i=0;i<order.size();++i){
 if(i) os<<',';
 os<<order[i];
 }
 movie.segment.tag_index["track.order"]=os.str();

}

}
