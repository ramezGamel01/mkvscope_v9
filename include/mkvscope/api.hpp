
#pragma once
#include "mkvscope/model.hpp"
#include <string>
#include <vector>
namespace mkv {

enum class InspectMode {
 Summary, Text, Json, Table, Full }
;
struct InspectResult {
 Movie movie;
 std::string report;
 bool ok{
};
 }
;
InspectResult inspect_bytes(const uint8_t* data, size_t size, InspectMode mode = InspectMode::Full);

InspectResult inspect_file(const std::string& path, InspectMode mode = InspectMode::Text);

void analyze_movie(Movie& movie);

}
