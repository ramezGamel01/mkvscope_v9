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

void catalog_codecs(Movie& movie){
 std::map<std::string,size_t> codecs;
 for(auto& t:movie.segment.tracks){
 for(auto& e:t.entries){
 std::string c=lower_ascii(e.codec_id);
 codecs[c]++;
 if(c.find("avc")!=std::string::npos && e.private_data.parameter_sets.empty()) movie.segment.warnings.push_back("avc-without-parameter-sets:"+std::to_string(t.number));
 if(c.find("opus")!=std::string::npos && e.channels>8) movie.segment.warnings.push_back("opus-channel-count-large:"+std::to_string(t.number));
 if(c.find("vp9")!=std::string::npos && e.private_data.profile>3) movie.segment.warnings.push_back("vp9-profile-invalid:"+std::to_string(t.number));
 }
 }
 std::ostringstream os;
 for(auto& kv:codecs) os<<kv.first<<'='<<kv.second<<';';
 movie.segment.tag_index["codec.catalog"]=os.str();
 }

}
