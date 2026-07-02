#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

void classify_codec_private(SampleEntry& entry);

void analyze_codec_private(SampleEntry& entry, Diagnostics& diag);

}
