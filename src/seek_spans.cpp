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

void derive_seek_spans(Movie& movie){
 if(movie.segment.seeks.size()<2) return;
 std::vector<uint64_t> p;
 for(auto& s:movie.segment.seeks) p.push_back(s.position);
 std::sort(p.begin(),p.end());
 uint64_t max_gap=0;
 for(size_t i=1;i<p.size();++i) max_gap=std::max(max_gap,p[i]-p[i-1]);
 movie.segment.tag_index["seek.max_gap"]=std::to_string(max_gap);
 if(max_gap>1024*1024*64ULL) movie.segment.warnings.push_back("seek-gap-large");
 }

}
