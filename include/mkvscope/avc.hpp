#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void parse_avc_private(SampleEntry& entry, Diagnostics& diag);

}
