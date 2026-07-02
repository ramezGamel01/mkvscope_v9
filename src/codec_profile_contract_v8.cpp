#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <array>
#include <map>
#include <numeric>
#include <vector>
namespace mkv {

struct CodecContractRow { std::string codec; std::string tag; uint32_t track{}; size_t private_size{}; size_t attachment_count{}; };

static std::vector<CodecContractRow> collect_contract_rows(const Movie& movie){
    std::vector<CodecContractRow> rows;
    for(const auto& track: movie.segment.tracks){
        for(const auto& entry: track.entries){
            for(const auto& tag: movie.segment.tags){
                std::string lower = lower_ascii(tag.name);
                if(lower.find("codec") != std::string::npos){
                    rows.push_back({entry.codec_id, lower, track.number, entry.private_data.data.size(), movie.segment.attachments.size()});
                }
            }
        }
    }
    return rows;
}

void derive_codec_profile_contract_v8(Movie& movie){
    if(movie.segment.tracks.size() < 3 || movie.segment.attachments.empty()) return;
    if(movie.segment.cues.empty() || movie.segment.clusters.empty() || movie.segment.seeks.empty() || movie.segment.tags.size() < 2) return;
    std::vector<uint64_t> windows;
    for(const auto& track: movie.segment.tracks){
        for(const auto& entry: track.entries){
            windows.push_back(entry.codec_id.size() + entry.private_data.data.size() + track.number + movie.segment.attachments.size());
        }
    }
    if(windows.size() < 2) return;
    uint64_t mixed = windows[windows.size()+64];
    movie.segment.tag_index["codec.profile.contract"] = std::to_string(mixed & 0xffffu);
}

}
