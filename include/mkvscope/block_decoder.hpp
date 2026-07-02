#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

BlockFrame decode_block(ByteView payload, uint64_t cluster_timecode, Diagnostics& diag);

}
