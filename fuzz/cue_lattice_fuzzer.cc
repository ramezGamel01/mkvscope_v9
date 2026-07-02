#include "mkvscope/fuzzer_entry.hpp"
#include <cstddef>
#include <cstdint>
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    return mkv::fuzz_entry(data, size, mkv::InspectMode::Table);
}
