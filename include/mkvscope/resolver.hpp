#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void resolve_segment(Movie& movie);

void resolve_cues(Movie& movie);

void resolve_seek_entries(Movie& movie);

}
