#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/element.hpp"
namespace mkv {

struct ElementInfo {
 uint64_t id;
 const char* name;
 bool master;
 }
;
const ElementInfo* schema_lookup(uint64_t id);

bool schema_allows_child(uint64_t parent, uint64_t child);

}
