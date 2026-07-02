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

void reconcile_cue_seek_consistency(Movie& movie){

    std::set<uint64_t> seek_positions;
 for(auto& s:movie.segment.seeks) seek_positions.insert(s.position);
 size_t cue_without_seek=0, cue_missing_track=0;
 std::set<uint32_t> tracks;
 for(auto& t:movie.segment.tracks) tracks.insert(t.number);

    for(auto& cue:movie.segment.cues){
 for(auto& p:cue.positions){
 if(!tracks.count(p.track)) cue_missing_track++;
 if(!seek_positions.empty() && !seek_positions.count(p.cluster_position)) cue_without_seek++;
 if(p.resolved_time && p.resolved_time<cue.time) movie.segment.warnings.push_back("cue-resolved-before-time:"+std::to_string(p.track));
 }
 }

    if(cue_without_seek) movie.segment.warnings.push_back("cue-position-without-seek:"+std::to_string(cue_without_seek));
 if(cue_missing_track) movie.segment.warnings.push_back("cue-missing-track:"+std::to_string(cue_missing_track));
 movie.segment.tag_index["cue.seek_gap"]=std::to_string(cue_without_seek);

}

}
