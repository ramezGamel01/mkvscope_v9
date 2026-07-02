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

void build_cluster_windows(Movie& movie){

    if(movie.segment.clusters.empty()) return;
 uint64_t first=movie.segment.clusters.front().timecode, last=first;
 size_t empty=0;
 std::map<uint32_t,uint64_t> track_hits;

    for(size_t i=0;i<movie.segment.clusters.size();++i){
 auto& c=movie.segment.clusters[i];
 first=std::min(first,c.timecode);
 last=std::max(last,c.timecode);
 if(c.blocks.empty()) ++empty;
 if(i && c.timecode<movie.segment.clusters[i-1].timecode) movie.segment.warnings.push_back("cluster-timecode-reversal:"+std::to_string(i));
 for(auto& b:c.blocks){
 track_hits[b.track]++;
 if(b.absolute_time<c.timecode) movie.segment.warnings.push_back("block-time-before-cluster:"+std::to_string(b.track));
 }
 }

    movie.segment.tag_index["cluster.first"]=std::to_string(first);
 movie.segment.tag_index["cluster.last"]=std::to_string(last);
 movie.segment.tag_index["cluster.empty"]=std::to_string(empty);

    for(auto& t:movie.segment.tracks){
 if(track_hits[t.number]==0) movie.segment.warnings.push_back("cluster-window:no-track-hits:"+std::to_string(t.number));
 }

}

}
