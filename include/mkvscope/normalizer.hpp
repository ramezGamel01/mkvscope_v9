#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void normalize_movie(Movie& movie);

void normalize_sample_entries(Movie& movie);

void normalize_tags(Movie& movie);

}
