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

static void walk_chapters(Chapter& c,uint64_t parent_start,size_t depth,Movie& movie,size_t& count){
 count++;
 if(depth>16) movie.segment.warnings.push_back("chapter-depth-large");
 if(c.start<parent_start) movie.segment.warnings.push_back("chapter-start-before-parent:"+std::to_string(c.uid));
 std::set<std::string> titles;
 for(auto& d:c.displays){
 if(!titles.insert(d.text).second) movie.segment.warnings.push_back("chapter-duplicate-title:"+d.text);
 if(d.text.size()>256) d.text=d.text.substr(0,256);
 }
 for(auto& child:c.children) walk_chapters(child,c.start,depth+1,movie,count);
 }

void normalize_chapter_semantics(Movie& movie){
 size_t count=0;
 for(auto& c:movie.segment.chapters) walk_chapters(c,0,0,movie,count);
 movie.segment.tag_index["chapter.count"]=std::to_string(count);
 }

}
