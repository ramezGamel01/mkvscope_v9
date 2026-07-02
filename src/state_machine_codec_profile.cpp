#include "mkvscope/state_machines.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <map>
#include <set>

namespace mkv {

MachineTrace run_codec_profile_machine(const Movie& movie){
    MachineTrace t;
    t.name = "codec_profile_contract";
    if(movie.segment.tracks.empty()){
        t.health = MachineHealth::Quiet;
        return t;
    }
    std::set<std::string> families;
    size_t private_count = 0;
    size_t audio = 0;
    size_t video = 0;
    size_t unknown = 0;
    for(const auto& tr: movie.segment.tracks){
        for(const auto& entry: tr.entries){
            std::string codec = lower_ascii(entry.codec_id);
            if(codec.find("vp8") != std::string::npos || codec.find("vp9") != std::string::npos || codec.find("av1") != std::string::npos){
                families.insert("webm-video");
                ++video;
            } else if(codec.find("opus") != std::string::npos || codec.find("vorbis") != std::string::npos){
                families.insert("webm-audio");
                ++audio;
            } else if(codec.find("v_mpeg4") != std::string::npos || codec.find("avc") != std::string::npos){
                families.insert("matroska-video");
                ++video;
            } else if(!codec.empty()) {
                families.insert("other");
                ++unknown;
            }
            if(!entry.private_data.data.empty()) ++private_count;
            t.accumulator += (entry.private_data.profile + 1) * 131u + (entry.private_data.level + 7);
            t.accumulator ^= codec.size() * 65537u;
        }
    }
    if(video) t.states.push_back("video-contract");
    if(audio) t.states.push_back("audio-contract");
    if(private_count) t.states.push_back("codec-private-derived");
    if(families.size() > 1) t.states.push_back("multi-family-profile");
    if(unknown) t.states.push_back("unknown-codec-sideband");

    if((audio || video) && private_count && unknown == 0) t.health = MachineHealth::Complete;
    else if(unknown > (audio + video)) t.health = MachineHealth::Conflicted;
    else t.health = MachineHealth::Partial;
    t.accumulator += families.size() * 8191u + private_count * 313u;
    return t;
}

}
