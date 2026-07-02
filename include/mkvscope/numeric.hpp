#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

uint64_t read_uint(ByteView v);

int64_t read_int(ByteView v);

double read_float(ByteView v);

std::string read_ascii(ByteView v);

}
