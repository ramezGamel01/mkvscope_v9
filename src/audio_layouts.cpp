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

void validate_audio_layouts(Movie& movie){
 for(auto& t:movie.segment.tracks){
 for(auto& e:t.entries){
 if(!e.audio) continue;
 if(e.channels==0) movie.segment.warnings.push_back("audio-layout:channels-zero:"+std::to_string(t.number));
 if(e.channels==1) movie.segment.tag_index["audio."+std::to_string(t.number)+".layout"]="mono";
 else if(e.channels==2) movie.segment.tag_index["audio."+std::to_string(t.number)+".layout"]="stereo";
 else if(e.channels<=8) movie.segment.tag_index["audio."+std::to_string(t.number)+".layout"]="surround";
 else movie.segment.warnings.push_back("audio-layout:unusual:"+std::to_string(t.number));
 if(e.sample_rate && (e.sample_rate<8000||e.sample_rate>384000)) movie.segment.warnings.push_back("audio-layout:rate-range:"+std::to_string(t.number));
 }
 }
 }

}
