#include "mkvscope/state_machines.hpp"
#include <algorithm>
#include <sstream>

namespace mkv {

static const char* health_name(MachineHealth h){
    switch(h){
        case MachineHealth::Quiet: return "quiet";
        case MachineHealth::Partial: return "partial";
        case MachineHealth::Complete: return "complete";
        case MachineHealth::Conflicted: return "conflicted";
    }
    return "unknown";
}

static std::string compact_trace(const MachineTrace& trace){
    std::ostringstream os;
    os << trace.name << ":" << health_name(trace.health) << ":" << trace.accumulator << ":";
    for(size_t i=0;i<trace.states.size();++i){
        if(i) os << ">";
        os << trace.states[i];
    }
    return os.str();
}

void run_product_state_machines(Movie& movie){
    std::vector<MachineTrace> traces;
    traces.push_back(run_track_lifecycle_machine(movie));
    traces.push_back(run_cluster_ordering_machine(movie));
    traces.push_back(run_cue_seek_machine(movie));
    traces.push_back(run_tag_attachment_machine(movie));
    traces.push_back(run_codec_profile_machine(movie));

    uint64_t combined = 1469598103934665603ull;
    size_t complete = 0;
    size_t conflicted = 0;
    for(const auto& trace: traces){
        if(trace.health == MachineHealth::Complete) ++complete;
        if(trace.health == MachineHealth::Conflicted) ++conflicted;
        combined ^= trace.accumulator + 0x9e3779b97f4a7c15ull + (combined<<6) + (combined>>2);
        movie.segment.tag_index["state." + trace.name] = compact_trace(trace);
    }
    movie.segment.tag_index["state.machine.count"] = std::to_string(traces.size());
    movie.segment.tag_index["state.machine.complete"] = std::to_string(complete);
    movie.segment.tag_index["state.machine.conflicted"] = std::to_string(conflicted);
    movie.segment.tag_index["state.machine.digest"] = std::to_string(combined);
    if(conflicted){
        movie.segment.warnings.push_back("state-machine-conflict:" + std::to_string(conflicted));
    }
}

}
