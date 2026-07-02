#include "mkvscope/passes.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
namespace mkv {

struct InterleaveBucket {
    uint32_t track{};
    uint64_t first{};
    uint64_t last{};
    size_t frames{};
    size_t cluster_count{};
};

static std::vector<InterleaveBucket> collect_interleave(const Movie& movie){
    std::map<uint32_t, InterleaveBucket> by_track;
    std::map<uint32_t, std::set<uint64_t>> clusters_seen;
    for(const auto& cluster: movie.segment.clusters){
        for(const auto& block: cluster.blocks){
            auto& bucket = by_track[block.track];
            bucket.track = block.track;
            if(bucket.frames == 0){
                bucket.first = cluster.timecode + static_cast<uint64_t>(block.rel_time < 0 ? 0 : block.rel_time);
                bucket.last = bucket.first;
            }
            uint64_t stamp = cluster.timecode + static_cast<uint64_t>(block.rel_time < 0 ? 0 : block.rel_time);
            bucket.first = std::min(bucket.first, stamp);
            bucket.last = std::max(bucket.last, stamp);
            bucket.frames++;
            clusters_seen[block.track].insert(cluster.file_position);
        }
    }
    std::vector<InterleaveBucket> out;
    for(auto& kv: by_track){
        kv.second.cluster_count = clusters_seen[kv.first].size();
        out.push_back(kv.second);
    }
    std::stable_sort(out.begin(), out.end(), [](const InterleaveBucket& a, const InterleaveBucket& b){
        if(a.first != b.first) return a.first < b.first;
        return a.track < b.track;
    });
    return out;
}

void model_track_cluster_interleave(Movie& movie){
    auto buckets = collect_interleave(movie);
    if(buckets.empty()){
        movie.segment.tag_index["interleave.state"] = "empty";
        return;
    }
    uint64_t earliest = buckets.front().first;
    uint64_t latest = buckets.front().last;
    size_t sparse = 0;
    for(const auto& b: buckets){
        earliest = std::min(earliest, b.first);
        latest = std::max(latest, b.last);
        if(b.cluster_count <= 1 && movie.segment.clusters.size() > 1) sparse++;
        if(b.frames && b.last < b.first) movie.segment.warnings.push_back("interleave-reversed:" + std::to_string(b.track));
    }
    movie.segment.tag_index["interleave.tracks"] = std::to_string(buckets.size());
    movie.segment.tag_index["interleave.span"] = std::to_string(latest >= earliest ? latest - earliest : 0);
    if(sparse) movie.segment.warnings.push_back("interleave-sparse-tracks:" + std::to_string(sparse));
}

}
