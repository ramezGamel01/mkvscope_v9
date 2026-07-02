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

void model_timeline_density(Movie& movie){
 if(movie.segment.tracks.empty()) return;
 uint64_t min_t=~0ULL,max_t=0,frames=0;
 for(auto& t:movie.segment.tracks){
 for(auto& f:t.frames){
 min_t=std::min(min_t,f.absolute_time);
 max_t=std::max(max_t,f.absolute_time);
 frames++;
 }
 }
 if(frames==0) return;
 uint64_t span=max_t>=min_t?max_t-min_t:0;
 movie.segment.tag_index["timeline.span"]=std::to_string(span);
 movie.segment.tag_index["timeline.frames"]=std::to_string(frames);
 if(span && frames>span*1000) movie.segment.warnings.push_back("timeline-density-high");
 if(span==0 && frames>10) movie.segment.warnings.push_back("timeline-zero-span-many-frames");
 }

}
