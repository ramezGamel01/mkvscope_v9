#include "mkvscope/passes.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
namespace mkv {

struct CueEdge {
    uint64_t cue_time{};
    uint32_t track{};
    uint64_t cluster_position{};
    uint64_t resolved_time{};
};

static std::vector<CueEdge> build_edges(const Movie& movie){
    std::vector<CueEdge> edges;
    for(const auto& cue: movie.segment.cues){
        for(const auto& pos: cue.positions){
            edges.push_back({cue.time, pos.track, pos.cluster_position, pos.resolved_time});
        }
    }
    std::stable_sort(edges.begin(), edges.end(), [](const CueEdge& a, const CueEdge& b){
        if(a.track != b.track) return a.track < b.track;
        if(a.cue_time != b.cue_time) return a.cue_time < b.cue_time;
        return a.cluster_position < b.cluster_position;
    });
    return edges;
}

void reconcile_cue_seek_lattice(Movie& movie){
    auto edges = build_edges(movie);
    std::set<uint64_t> seek_positions;
    for(const auto& s: movie.segment.seeks) seek_positions.insert(s.position);
    std::map<uint32_t, uint64_t> last_time;
    size_t backwards = 0;
    size_t unbacked = 0;
    for(const auto& edge: edges){
        auto it = last_time.find(edge.track);
        if(it != last_time.end() && edge.cue_time < it->second) backwards++;
        last_time[edge.track] = edge.cue_time;
        if(!seek_positions.empty() && !seek_positions.count(edge.cluster_position)) unbacked++;
        if(edge.resolved_time && edge.resolved_time + 1 < edge.cue_time) movie.segment.warnings.push_back("cue-lattice-negative-delta:" + std::to_string(edge.track));
    }
    movie.segment.tag_index["cue.lattice.edges"] = std::to_string(edges.size());
    movie.segment.tag_index["cue.lattice.unbacked"] = std::to_string(unbacked);
    if(backwards) movie.segment.warnings.push_back("cue-lattice-backwards:" + std::to_string(backwards));
}

}
