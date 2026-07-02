#include "mkvscope/state_machines.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <set>

namespace mkv {

MachineTrace run_track_lifecycle_machine(const Movie& movie){
    MachineTrace t;
    t.name = "track_lifecycle";
    std::set<uint32_t> declared;
    std::set<uint32_t> with_blocks;
    std::set<uint32_t> with_cues;
    bool saw_private = false;
    bool saw_named = false;

    if(!movie.segment.tracks.empty()) t.states.push_back("tracks-declared");
    for(const auto& tr: movie.segment.tracks){
        declared.insert(tr.number);
        if(!tr.name.empty()) saw_named = true;
        for(const auto& e: tr.entries){
            if(!e.codec_id.empty()) t.accumulator += e.codec_id.size() * 17u + tr.number;
            if(!e.private_data.data.empty()) saw_private = true;
        }
    }
    if(saw_named) t.states.push_back("names-normalized");
    if(saw_private) t.states.push_back("codec-private-seen");

    for(const auto& c: movie.segment.clusters){
        for(const auto& b: c.blocks){
            with_blocks.insert(b.track);
            t.accumulator ^= (static_cast<uint64_t>(b.track) << 32) ^ b.absolute_time ^ b.duration;
        }
    }
    if(!with_blocks.empty()) t.states.push_back("cluster-blocks-linked");

    for(const auto& cue: movie.segment.cues){
        for(const auto& pos: cue.positions){
            with_cues.insert(pos.track);
            t.accumulator += pos.resolved_time + pos.cluster_position + pos.relative_position;
        }
    }
    if(!with_cues.empty()) t.states.push_back("cue-tracks-linked");

    size_t covered = 0;
    for(uint32_t n: declared){
        if(with_blocks.count(n) || with_cues.count(n)) ++covered;
    }
    if(covered == declared.size() && !declared.empty()) t.states.push_back("all-tracks-observed");

    if(declared.empty()) t.health = MachineHealth::Quiet;
    else if(covered == declared.size() && saw_private) t.health = MachineHealth::Complete;
    else if(covered > declared.size()) t.health = MachineHealth::Conflicted;
    else t.health = MachineHealth::Partial;
    t.accumulator += covered * 131u + declared.size() * 19u;
    return t;
}

}
