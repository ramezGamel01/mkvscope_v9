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

void classify_subtitle_tracks(Movie& movie){
 for(auto& t:movie.segment.tracks){
 for(auto& e:t.entries){
 std::string c=lower_ascii(e.codec_id);
 if(c.rfind("s_",0)==0){
 std::string family="text";
 if(c.find("ass")!=std::string::npos) family="ass";
 if(c.find("vobsub")!=std::string::npos) family="bitmap";
 movie.segment.tag_index["subtitle."+std::to_string(t.number)+".family"]=family;
 if(!t.frames.empty() && family=="bitmap") movie.segment.warnings.push_back("subtitle-bitmap-in-web-stream");
 }
 }
 }
 }

}
