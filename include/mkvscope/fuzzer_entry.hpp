#pragma once
#include "mkvscope/api.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

int fuzz_entry(const uint8_t* data, size_t size, InspectMode mode);

}
