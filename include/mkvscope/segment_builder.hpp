#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

Movie build_movie(Document& doc);

void populate_segment_from_element(const Element& segment, Movie& movie);

}
