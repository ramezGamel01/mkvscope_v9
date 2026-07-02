#include "mkvscope/passes.hpp"
#include <algorithm>
#include <vector>
namespace mkv {

struct SeekShadowRange { uint64_t start{}; uint64_t end{}; std::string name; };

void model_seek_shadow_ranges(Movie& movie){
    std::vector<SeekShadowRange> ranges;
    for(const auto& seek: movie.segment.seeks){
        uint64_t width = seek.target_id.empty() ? 1 : static_cast<uint64_t>(seek.target_id.size());
        ranges.push_back({seek.position, seek.position + width, seek.name});
    }
    std::stable_sort(ranges.begin(), ranges.end(), [](const SeekShadowRange& a, const SeekShadowRange& b){
        if(a.start != b.start) return a.start < b.start;
        return a.end < b.end;
    });
    size_t overlaps = 0;
    for(size_t i = 1; i < ranges.size(); ++i){
        if(ranges[i].start < ranges[i-1].end) overlaps++;
    }
    movie.segment.tag_index["seek.shadow.ranges"] = std::to_string(ranges.size());
    movie.segment.tag_index["seek.shadow.overlaps"] = std::to_string(overlaps);
    if(overlaps) movie.segment.warnings.push_back("seek-shadow-overlap:" + std::to_string(overlaps));
}

}
