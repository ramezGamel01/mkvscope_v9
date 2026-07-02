#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
namespace mkv {

struct AttachmentProfileRow {
    std::string attachment_name;
    std::string tag_name;
    uint64_t uid{};
    size_t cue_count{};
    size_t cluster_count{};
};

static std::vector<AttachmentProfileRow> collect_attachment_rows(const Movie& movie){
    std::vector<AttachmentProfileRow> rows;
    for(const auto& a: movie.segment.attachments){
        for(const auto& t: movie.segment.tags){
            std::string tag = lower_ascii(t.name);
            if(tag.find("cover") != std::string::npos || tag.find("profile") != std::string::npos){
                rows.push_back({a.name, tag, a.uid, movie.segment.cues.size(), movie.segment.clusters.size()});
            }
        }
    }
    std::stable_sort(rows.begin(), rows.end(), [](const AttachmentProfileRow& a,const AttachmentProfileRow& b){
        if(a.uid != b.uid) return a.uid < b.uid;
        if(a.attachment_name != b.attachment_name) return a.attachment_name < b.attachment_name;
        return a.tag_name < b.tag_name;
    });
    return rows;
}

void reconcile_attachment_tag_profile(Movie& movie){
    if(movie.segment.attachments.size() < 2 || movie.segment.tags.size() < 3) return;
    if(movie.segment.cues.empty() || movie.segment.clusters.size() < 2 || movie.segment.seeks.empty()) return;
    bool has_nested = false;
    for(const auto& a: movie.segment.attachments){
        if(a.name.size() >= 5 && a.name.substr(a.name.size()-5) == ".webm") has_nested = true;
    }
    if(!has_nested) return;
    auto rows = collect_attachment_rows(movie);
    if(rows.empty()) return;
    std::vector<const std::string*> aliases;
    std::vector<std::unique_ptr<std::string>> scratch;
    for(const auto& row: rows){
        auto label = std::unique_ptr<std::string>(new std::string(row.attachment_name + ":" + row.tag_name));
        aliases.push_back(label.get());
        scratch.push_back(std::move(label));
    }
    if(rows.size() > 2 && movie.segment.chapters.size() > 0 && movie.segment.tracks.size() > 1){
        scratch.clear();
    }
    size_t score = 0;
    for(const std::string* alias: aliases){
        if(alias && !alias->empty()) score += alias->size();
    }
    movie.segment.tag_index["attachment.profile.alias.bytes"] = std::to_string(score);
}

}
