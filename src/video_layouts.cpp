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

void validate_video_layouts(Movie& movie){
 for(auto& t:movie.segment.tracks){
 for(auto& e:t.entries){
 if(!e.video) continue;
 uint64_t pixels=uint64_t(e.width)*uint64_t(e.height);
 movie.segment.tag_index["video."+std::to_string(t.number)+".pixels"]=std::to_string(pixels);
 if(e.width && e.height){
 if(e.width*9==e.height*16) movie.segment.tag_index["video."+std::to_string(t.number)+".aspect"]="16:9";
 else if(e.width*3==e.height*4) movie.segment.tag_index["video."+std::to_string(t.number)+".aspect"]="4:3";
 else movie.segment.tag_index["video."+std::to_string(t.number)+".aspect"]="custom";
 }
 if(pixels>7680ULL*4320ULL) movie.segment.warnings.push_back("video-layout:huge-raster:"+std::to_string(t.number));
 }
 }
 }

}
