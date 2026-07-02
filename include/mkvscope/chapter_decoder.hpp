#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void decode_chapters(const Element& chapters, Movie& movie);

void resolve_chapter_displays(Movie& movie);

}
