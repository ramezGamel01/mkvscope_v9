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

static std::string ext_of(const std::string& n){
 auto p=n.find_last_of('.');
 return p==std::string::npos?std::string():lower_ascii(n.substr(p+1));
 }

void catalog_attachments(Movie& movie){
 std::map<std::string,size_t> by_ext;
 uint64_t total=0;
 for(auto& a:movie.segment.attachments){
 by_ext[ext_of(a.name)]++;
 total+=a.data.size();
 if(a.data.empty()) movie.segment.warnings.push_back("attachment-empty:"+a.name);
 if(a.name.find('/')!=std::string::npos||a.name.find('\\')!=std::string::npos) movie.segment.warnings.push_back("attachment-pathlike:"+a.name);
 if(a.probe.find("inner:")==0) movie.segment.tag_index["attachment.inner"]="yes";
 }
 for(auto& kv:by_ext) movie.segment.tag_index["attachment.ext."+kv.first]=std::to_string(kv.second);
 movie.segment.tag_index["attachment.bytes"]=std::to_string(total);
 }

}
