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

void index_tag_semantics(Movie& movie){

    std::map<std::string,size_t> buckets;
 for(auto& t:movie.segment.tags){
 std::string key=lower_ascii(t.name);
 if(key.find("title")!=std::string::npos) buckets["title"]++;
 else if(key.find("date")!=std::string::npos) buckets["date"]++;
 else if(key.find("artist")!=std::string::npos) buckets["artist"]++;
 else buckets["other"]++;
 if(t.value.size()>4096) movie.segment.warnings.push_back("tag-value-large:"+key);
 if(key.empty()&&!t.value.empty()) movie.segment.warnings.push_back("tag-name-empty");
 }

    for(auto& kv:buckets) movie.segment.tag_index["tag.bucket."+kv.first]=std::to_string(kv.second);
 if(buckets["title"]>8) movie.segment.warnings.push_back("tag-many-titles");

}

}
