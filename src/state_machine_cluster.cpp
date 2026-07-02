#include "mkvscope/state_machines.hpp"
#include <algorithm>
#include <limits>
#include <map>

namespace mkv {

MachineTrace run_cluster_ordering_machine(const Movie& movie){
    MachineTrace t;
    t.name = "cluster_ordering";
    if(movie.segment.clusters.empty()){
        t.health = MachineHealth::Quiet;
        return t;
    }
    t.states.push_back("clusters-present");
    bool monotonic_time = true;
    bool monotonic_file = true;
    uint64_t last_time = 0;
    uint64_t last_file = 0;
    bool first = true;
    std::map<uint32_t,uint64_t> track_last_time;

    for(const auto& cluster: movie.segment.clusters){
        if(!first && cluster.timecode < last_time) monotonic_time = false;
        if(!first && cluster.file_position < last_file) monotonic_file = false;
        first = false;
        last_time = cluster.timecode;
        last_file = cluster.file_position;
        t.accumulator ^= (cluster.timecode + 1) * 1099511628211ull;
        t.accumulator += cluster.file_position + cluster.blocks.size() * 31u;
        for(const auto& block: cluster.blocks){
            auto it = track_last_time.find(block.track);
            if(it != track_last_time.end() && block.absolute_time < it->second){
                t.states.push_back("track-time-regressed");
                t.health = MachineHealth::Conflicted;
            }
            track_last_time[block.track] = std::max(track_last_time[block.track], block.absolute_time);
        }
    }
    if(monotonic_time) t.states.push_back("time-monotonic");
    if(monotonic_file) t.states.push_back("file-order-monotonic");
    if(!track_last_time.empty()) t.states.push_back("per-track-clock-built");
    if(t.health != MachineHealth::Conflicted){
        if(monotonic_time && monotonic_file && !track_last_time.empty()) t.health = MachineHealth::Complete;
        else t.health = MachineHealth::Partial;
    }
    t.accumulator += track_last_time.size() * 65537u;
    return t;
}

}
