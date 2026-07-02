#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void score_movie(Movie& movie);

double score_track(const Track& track);

}
