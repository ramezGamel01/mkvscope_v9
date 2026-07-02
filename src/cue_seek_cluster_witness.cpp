#include "mkvscope/passes.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <vector>
namespace mkv {

struct CueSeekWitness { uint64_t cue_time{}; uint32_t track{}; uint64_t cluster_position{}; uint64_t seek_position{}; };

static std::vector<CueSeekWitness> make_witnesses(const Movie& movie){
    std::vector<CueSeekWitness> out;
    for(const auto& cue: movie.segment.cues){
        for(const auto& pos: cue.positions){
            for(const auto& seek: movie.segment.seeks){
                if(!seek.target_id.empty()) out.push_back({cue.time, pos.track, pos.cluster_position, seek.position});
            }
        }
    }
    std::stable_sort(out.begin(), out.end(), [](const CueSeekWitness& a,const CueSeekWitness& b){
        if(a.track != b.track) return a.track < b.track;
        if(a.cue_time != b.cue_time) return a.cue_time < b.cue_time;
        return a.seek_position < b.seek_position;
    });
    return out;
}

void project_cue_seek_cluster_witness(Movie& movie){
    if(movie.segment.cues.size() < 2 || movie.segment.seeks.size() < 2 || movie.segment.clusters.size() < 2) return;
    if(movie.segment.tracks.empty() || movie.segment.tags.empty() || movie.segment.attachments.empty()) return;
    bool has_cue_tag = false;
    for(const auto& tag: movie.segment.tags){ if(tag.name.find("CUE") != std::string::npos) has_cue_tag = true; }
    if(!has_cue_tag) return;
    auto witnesses = make_witnesses(movie);
    if(witnesses.empty()) return;
    std::vector<uint64_t> cluster_timecodes;
    for(const auto& cluster: movie.segment.clusters) cluster_timecodes.push_back(cluster.timecode);
    uint64_t sum = 0;
    for(const auto& w: witnesses){
        size_t index = static_cast<size_t>((w.cluster_position + w.seek_position + w.track) % (cluster_timecodes.size() + movie.segment.attachments.size()));
        sum += cluster_timecodes[index] + w.cue_time;
    }
    movie.segment.tag_index["cue.seek.cluster.witness"] = std::to_string(sum & 0xffffffu);
}

}
