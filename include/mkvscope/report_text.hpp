#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
#include <ostream>
namespace mkv {

std::string movie_text_report(const Movie& movie);

void write_text_report(std::ostream& os, const Movie& movie);

}
