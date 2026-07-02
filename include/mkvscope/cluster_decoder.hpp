#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void decode_cluster(const Element& cluster, Movie& movie);

}
