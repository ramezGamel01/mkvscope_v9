#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
namespace mkv {

static std::string codec_family(const SampleEntry& e){
    std::string c = lower_ascii(e.codec_id);
    if(c.find("vp9") != std::string::npos) return "vp9";
    if(c.find("av1") != std::string::npos) return "av1";
    if(c.find("avc") != std::string::npos || c.find("mpeg4") != std::string::npos) return "avc";
    if(c.find("opus") != std::string::npos) return "opus";
    if(c.find("vorbis") != std::string::npos) return "vorbis";
    return c.empty() ? "unknown" : c;
}

void derive_codec_transition_graph(Movie& movie){
    std::map<std::string, size_t> family_counts;
    std::set<std::string> transitions;
    for(const auto& track: movie.segment.tracks){
        std::string prev;
        for(const auto& entry: track.entries){
            std::string fam = codec_family(entry);
            family_counts[fam]++;
            if(!prev.empty() && prev != fam) transitions.insert(prev + ">" + fam);
            prev = fam;
            if(entry.video && (entry.width == 0 || entry.height == 0)) movie.segment.warnings.push_back("codec-video-layout-missing:" + std::to_string(track.number));
            if(entry.audio && entry.channels == 0) movie.segment.warnings.push_back("codec-audio-layout-missing:" + std::to_string(track.number));
        }
    }
    for(const auto& kv: family_counts) movie.segment.tag_index["codec.family." + kv.first] = std::to_string(kv.second);
    movie.segment.tag_index["codec.transitions"] = std::to_string(transitions.size());
}

}
