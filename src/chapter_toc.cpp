#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <sstream>
namespace mkv {

static void flatten_chapter(const Chapter& ch, unsigned depth, std::vector<std::string>& out, uint64_t& last_start, size_t& nonmono){
    std::string label;
    if(!ch.displays.empty()) label = ch.displays.front().text;
    if(label.empty()) label = "chapter-" + std::to_string(ch.uid);
    out.push_back(std::to_string(depth) + ":" + std::to_string(ch.start) + ":" + label);
    if(out.size() > 1 && ch.start < last_start) nonmono++;
    last_start = std::max(last_start, ch.start);
    for(const auto& child: ch.children) flatten_chapter(child, depth + 1, out, last_start, nonmono);
}

void synthesize_chapter_toc(Movie& movie){
    std::vector<std::string> rows;
    uint64_t last = 0;
    size_t nonmono = 0;
    for(const auto& ch: movie.segment.chapters) flatten_chapter(ch, 0, rows, last, nonmono);
    movie.segment.tag_index["chapters.toc.rows"] = std::to_string(rows.size());
    if(!rows.empty()) movie.segment.tag_index["chapters.toc.first"] = rows.front().substr(0, std::min<size_t>(rows.front().size(), 48));
    if(nonmono) movie.segment.warnings.push_back("chapter-toc-nonmonotonic:" + std::to_string(nonmono));
}

}
