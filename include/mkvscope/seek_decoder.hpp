#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void decode_seek_head(const Element& seekhead, Movie& movie);

}
