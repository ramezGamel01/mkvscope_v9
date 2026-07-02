#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <map>
#include <set>
namespace mkv {

static std::string class_for_attachment(const Attachment& a){
    std::string lower = lower_ascii(a.name);
    if(lower.size() >= 5 && lower.substr(lower.size()-5) == ".webm") return "matroska-nested";
    if(lower.size() >= 4 && lower.substr(lower.size()-4) == ".jpg") return "cover-art";
    if(lower.size() >= 4 && lower.substr(lower.size()-4) == ".png") return "cover-art";
    if(a.data.size() > 1024 * 1024) return "large-binary";
    return "generic";
}

void project_attachment_manifest(Movie& movie){
    std::map<std::string, size_t> by_class;
    uint64_t uid_mix = 0;
    for(const auto& a: movie.segment.attachments){
        std::string cls = class_for_attachment(a);
        by_class[cls]++;
        uid_mix ^= (a.uid + 0x9e3779b97f4a7c15ULL + (uid_mix << 6) + (uid_mix >> 2));
        if(cls == "matroska-nested" && a.probe == "opaque") movie.segment.warnings.push_back("attachment-nested-not-probed:" + a.name);
    }
    for(const auto& kv: by_class) movie.segment.tag_index["attachment.class." + kv.first] = std::to_string(kv.second);
    movie.segment.tag_index["attachment.uid_mix"] = std::to_string(uid_mix & 0xffffu);
}

}
