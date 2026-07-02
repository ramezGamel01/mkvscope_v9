#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void decode_attachments(const Element& attachments, Movie& movie);

void probe_attachments(Movie& movie);

}
