#include "mkvscope/state_machines.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <map>
#include <set>

namespace mkv {

MachineTrace run_tag_attachment_machine(const Movie& movie){
    MachineTrace t;
    t.name = "tag_attachment_binding";
    if(movie.segment.tags.empty() && movie.segment.attachments.empty()){
        t.health = MachineHealth::Quiet;
        return t;
    }
    if(!movie.segment.tags.empty()) t.states.push_back("tags-present");
    if(!movie.segment.attachments.empty()) t.states.push_back("attachments-present");

    std::set<uint64_t> attachment_uids;
    std::set<std::string> attachment_names;
    for(const auto& a: movie.segment.attachments){
        attachment_uids.insert(a.uid);
        attachment_names.insert(lower_ascii(a.name));
        t.accumulator += a.uid ^ (a.data.size() * 257u);
    }
    bool tag_mentions_attachment = false;
    bool cover_semantics = false;
    bool profile_semantics = false;
    for(const auto& tag: movie.segment.tags){
        std::string name = lower_ascii(tag.name);
        std::string value = lower_ascii(tag.value);
        if(name.find("cover") != std::string::npos || value.find("cover") != std::string::npos) cover_semantics = true;
        if(name.find("profile") != std::string::npos || value.find("profile") != std::string::npos) profile_semantics = true;
        for(const auto& an: attachment_names){
            if(!an.empty() && value.find(an) != std::string::npos){ tag_mentions_attachment = true; }
        }
        t.accumulator ^= (name.size() + 11) * (value.size() + 23);
    }
    if(tag_mentions_attachment) t.states.push_back("tag-names-attachment");
    if(cover_semantics) t.states.push_back("cover-art-semantics");
    if(profile_semantics) t.states.push_back("profile-tag-semantics");

    if(!movie.segment.attachments.empty() && movie.segment.tags.empty()) t.health = MachineHealth::Partial;
    else if(tag_mentions_attachment || (cover_semantics && !attachment_uids.empty())) t.health = MachineHealth::Complete;
    else if(profile_semantics && attachment_uids.empty()) t.health = MachineHealth::Conflicted;
    else t.health = MachineHealth::Partial;
    t.accumulator += attachment_uids.size() * 4099u;
    return t;
}

}
