#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

std::vector<BlockFrame> split_laced_block(const BlockFrame& block, Diagnostics& diag);

std::vector<size_t> parse_lace_sizes(ByteView payload, size_t off, uint8_t flags, Diagnostics& diag);

}
