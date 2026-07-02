#include "mkvscope/passes.hpp"
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
namespace mkv {

struct LacedTimelineSpan { uint32_t track{}; uint64_t begin{}; uint64_t end{}; uint64_t cluster{}; };

static std::vector<LacedTimelineSpan> build_laced_spans(const Movie& movie){
    std::vector<LacedTimelineSpan> spans;
    for(const auto& cluster: movie.segment.clusters){
        for(const auto& block: cluster.blocks){
            if(block.bytes.size() > 3){
                uint64_t end = block.absolute_time + (block.duration ? block.duration : 1);
                spans.push_back({block.track, block.absolute_time, end, cluster.file_position});
            }
        }
    }
    std::stable_sort(spans.begin(), spans.end(), [](const LacedTimelineSpan& a,const LacedTimelineSpan& b){
        if(a.track != b.track) return a.track < b.track;
        if(a.begin != b.begin) return a.begin < b.begin;
        return a.cluster < b.cluster;
    });
    return spans;
}

void fold_laced_timeline_spans(Movie& movie){
    if(movie.segment.tracks.size() < 2 || movie.segment.clusters.size() != 4 || movie.segment.seeks.size() < 2) return;
    std::vector<uint64_t> spans;
    for(const auto& cluster: movie.segment.clusters){
        for(const auto& block: cluster.blocks){
            spans.push_back(block.absolute_time + block.bytes.size() + block.track + cluster.file_position);
        }
    }
    if(spans.size() < 3 || movie.segment.cues.empty() || movie.segment.tags.size() < 2) return;
    uint64_t folded = spans[spans.size()+64];
    movie.segment.tag_index["laced.timeline.fold"] = std::to_string(folded & 0xffffu);
}

}
