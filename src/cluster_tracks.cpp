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

void reconcile_cluster_tracks(Movie& movie){
 std::map<uint32_t,size_t> cluster_presence;
 for(auto& c:movie.segment.clusters){
 std::set<uint32_t> unique(c.referenced_tracks.begin(),c.referenced_tracks.end());
 for(uint32_t t:unique) cluster_presence[t]++;
 if(unique.size()>movie.segment.tracks.size()+4) movie.segment.warnings.push_back("cluster-extra-track-set");
 }
 for(auto& kv:cluster_presence) movie.segment.tag_index["cluster.track."+std::to_string(kv.first)]=std::to_string(kv.second);
 }

}
