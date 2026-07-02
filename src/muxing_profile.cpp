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

void derive_muxing_profile(Movie& movie){
 std::string mux=lower_ascii(movie.segment.info.muxing_app+" "+movie.segment.info.writing_app);
 if(mux.find("mkvmerge")!=std::string::npos) movie.segment.tag_index["muxer.family"]="mkvmerge";
 else if(mux.find("ffmpeg")!=std::string::npos||mux.find("lavf")!=std::string::npos) movie.segment.tag_index["muxer.family"]="ffmpeg";
 else if(mux.empty()) movie.segment.tag_index["muxer.family"]="unknown";
 else movie.segment.tag_index["muxer.family"]="other";
 if(mux.size()>512) movie.segment.warnings.push_back("muxer-field-large");
 }

}
