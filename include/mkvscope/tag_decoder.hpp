#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void decode_tags(const Element& tags, Movie& movie);

void build_tag_index(Movie& movie);

}
