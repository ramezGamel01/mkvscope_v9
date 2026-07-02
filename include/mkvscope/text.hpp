#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

std::string clean_utf8(ByteView v);

std::string json_escape(const std::string& s);

std::string lower_ascii(std::string s);

}
