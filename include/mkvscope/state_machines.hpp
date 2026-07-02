#pragma once
#include "mkvscope/model.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace mkv {

enum class MachineHealth { Quiet, Partial, Complete, Conflicted };

struct MachineTrace {
    std::string name;
    std::vector<std::string> states;
    MachineHealth health{MachineHealth::Quiet};
    uint64_t accumulator{};
};

MachineTrace run_track_lifecycle_machine(const Movie& movie);
MachineTrace run_cluster_ordering_machine(const Movie& movie);
MachineTrace run_cue_seek_machine(const Movie& movie);
MachineTrace run_tag_attachment_machine(const Movie& movie);
MachineTrace run_codec_profile_machine(const Movie& movie);

void run_product_state_machines(Movie& movie);

}
