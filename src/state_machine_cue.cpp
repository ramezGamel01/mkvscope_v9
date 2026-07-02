#include "mkvscope/state_machines.hpp"
#include <algorithm>
#include <map>
#include <set>

namespace mkv {

MachineTrace run_cue_seek_machine(const Movie& movie){
    MachineTrace t;
    t.name = "cue_seek_lattice";
    if(movie.segment.cues.empty() && movie.segment.seeks.empty()){
        t.health = MachineHealth::Quiet;
        return t;
    }
    if(!movie.segment.seeks.empty()) t.states.push_back("seekhead-present");
    if(!movie.segment.cues.empty()) t.states.push_back("cues-present");

    std::set<uint64_t> cluster_positions;
    for(const auto& c: movie.segment.clusters){
        cluster_positions.insert(c.file_position);
    }
    if(!cluster_positions.empty()) t.states.push_back("cluster-position-indexed");

    size_t resolved = 0;
    size_t dangling = 0;
    uint64_t last_time = 0;
    bool time_sorted = true;
    bool first = true;
    for(const auto& cue: movie.segment.cues){
        if(!first && cue.time < last_time) time_sorted = false;
        first = false;
        last_time = cue.time;
        for(const auto& pos: cue.positions){
            bool exact = cluster_positions.count(pos.cluster_position) != 0;
            bool near = false;
            if(!exact){
                auto it = cluster_positions.lower_bound(pos.cluster_position);
                if(it != cluster_positions.end() && *it <= pos.cluster_position + 16) near = true;
            }
            if(exact || near) ++resolved; else ++dangling;
            t.accumulator ^= (cue.time + 3) * (pos.track + 17);
            t.accumulator += pos.cluster_position ^ (pos.resolved_time << 1);
        }
    }
    if(time_sorted) t.states.push_back("cue-time-sorted");
    if(resolved) t.states.push_back("cue-targets-resolved");
    if(dangling) t.states.push_back("cue-targets-dangling");
    if(dangling > resolved && !movie.segment.cues.empty()) t.health = MachineHealth::Conflicted;
    else if(resolved && time_sorted) t.health = MachineHealth::Complete;
    else t.health = MachineHealth::Partial;
    t.accumulator += resolved * 1009u + dangling * 9176u;
    return t;
}

}
