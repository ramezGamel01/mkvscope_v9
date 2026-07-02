
#pragma once
#include "mkvscope/bytes.hpp"
#include <cstdint>
namespace mkv {

struct VInt {
 uint64_t value{
};
 unsigned width{
};
 bool unknown{
};
 bool valid{
};
 }
;
VInt read_vint(ByteView v, size_t off, bool clear_marker=true);

VInt read_id(ByteView v, size_t off);

unsigned vint_width(uint8_t first);

std::vector<uint8_t> encode_id(uint64_t id);

std::vector<uint8_t> encode_size(uint64_t size);

}
