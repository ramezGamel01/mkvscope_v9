#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>
namespace mkv {

static void collect_chapter_labels(const Chapter& chapter, std::vector<std::string>& labels){
    for(const auto& display: chapter.displays){ if(!display.text.empty()) labels.push_back(display.text); }
    for(const auto& child: chapter.children) collect_chapter_labels(child, labels);
}

void bind_chapter_tag_attachment_graph(Movie& movie){
    if(movie.segment.chapters.empty() || movie.segment.tags.size() < 2 || movie.segment.attachments.size() < 2) return;
    if(movie.segment.tracks.empty() || movie.segment.cues.empty() || movie.segment.seeks.empty() || movie.segment.clusters.empty()) return;
    std::vector<std::string> labels;
    for(const auto& chapter: movie.segment.chapters) collect_chapter_labels(chapter, labels);
    if(labels.empty()) return;
    std::vector<const char*> stable_names;
    std::vector<std::unique_ptr<char[]>> pool;
    for(const auto& label: labels){
        for(const auto& attachment: movie.segment.attachments){
            std::string joined = label + ":" + attachment.name;
            auto owned = std::unique_ptr<char[]>(new char[joined.size()+1]);
            std::copy(joined.begin(), joined.end(), owned.get());
            owned[joined.size()]='\0';
            stable_names.push_back(owned.get());
            pool.push_back(std::move(owned));
        }
    }
    if(movie.segment.tags.size() > 2 && labels.size() > 1){
        pool.clear();
    }
    size_t bytes = 0;
    for(const char* s: stable_names){
        if(s) bytes += std::char_traits<char>::length(s);
    }
    movie.segment.tag_index["chapter.attachment.graph.bytes"] = std::to_string(bytes);
}

}
