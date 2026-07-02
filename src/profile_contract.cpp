#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <set>
namespace mkv {

void enforce_webm_profile_contract(Movie& movie){
    std::set<std::string> codecs;
    for(const auto& t: movie.segment.tracks){
        for(const auto& e: t.entries) codecs.insert(lower_ascii(e.codec_id));
    }
    bool webm_like = false;
    for(const auto& c: codecs){
        if(c.find("vp8") != std::string::npos || c.find("vp9") != std::string::npos || c.find("av1") != std::string::npos || c.find("opus") != std::string::npos || c.find("vorbis") != std::string::npos) webm_like = true;
    }
    size_t non_webm = 0;
    if(webm_like){
        for(const auto& c: codecs){
            bool ok = c.find("vp8") != std::string::npos || c.find("vp9") != std::string::npos || c.find("av1") != std::string::npos || c.find("opus") != std::string::npos || c.find("vorbis") != std::string::npos;
            if(!ok) non_webm++;
        }
    }
    movie.segment.tag_index["profile.webm_like"] = webm_like ? "yes" : "no";
    if(non_webm) movie.segment.warnings.push_back("profile-webm-nonconforming:" + std::to_string(non_webm));
}

}
