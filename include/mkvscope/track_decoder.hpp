#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void decode_tracks(const Element& tracks, Movie& movie);

}
