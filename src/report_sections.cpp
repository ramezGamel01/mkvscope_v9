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

void derive_report_sections(Movie& movie){
 std::vector<std::string> sections;
 if(!movie.segment.tracks.empty()) sections.push_back("tracks");
 if(!movie.segment.clusters.empty()) sections.push_back("clusters");
 if(!movie.segment.cues.empty()) sections.push_back("cues");
 if(!movie.segment.tags.empty()) sections.push_back("tags");
 if(!movie.segment.attachments.empty()) sections.push_back("attachments");
 if(!movie.segment.chapters.empty()) sections.push_back("chapters");
 std::ostringstream os;
 for(size_t i=0;i<sections.size();++i){
 if(i) os<<',';
 os<<sections[i];
 }
 movie.segment.tag_index["report.sections"]=os.str();
 }

}
