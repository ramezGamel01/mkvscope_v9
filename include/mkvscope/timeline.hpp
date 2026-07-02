#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void materialize_timeline(Movie& movie);

void apply_timecode_scale(Movie& movie);

}
