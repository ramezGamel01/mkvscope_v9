#include "mkvscope/passes.hpp"
#include "mkvscope/text.hpp"
#include "mkvscope/ids.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <unordered_map>
namespace mkv {

static bool starts(const std::string& a,const std::string& b){
 return a.rfind(b,0)==0;
 }

void classify_matroska_profile(Movie& movie){

    bool webm=movie.doc_type=="webm";
 bool has_video=false, has_audio=false, has_subtitle=false;
 std::set<std::string> families;

    for(auto& t: movie.segment.tracks){
 for(auto& e:t.entries){
 std::string c=lower_ascii(e.codec_id);
 if(starts(c,"v_")){
 has_video=true;
 families.insert("video");
 }
 if(starts(c,"a_")){
 has_audio=true;
 families.insert("audio");
 }
 if(starts(c,"s_")){
 has_subtitle=true;
 families.insert("subtitle");
 }
 if(webm && c.find("avc")!=std::string::npos) movie.segment.warnings.push_back("webm:non-webm-video-codec");
 if(webm && c.find("vorbis")==std::string::npos && starts(c,"a_") && c.find("opus")==std::string::npos) movie.segment.warnings.push_back("webm:non-webm-audio-codec");
 }
 }

    std::string profile = webm ? "webm" : "matroska";
 if(has_video&&has_audio) profile += ":av";
 else if(has_video) profile += ":video";
 else if(has_audio) profile += ":audio";
 else if(has_subtitle) profile += ":text";
 else profile += ":metadata";

    movie.segment.tag_index["profile.container"]=profile;
 movie.segment.tag_index["profile.family_count"]=std::to_string(families.size());

    if(movie.segment.attachments.size()>32) movie.segment.warnings.push_back("profile:many-attachments");

    if(movie.segment.chapters.size()>256) movie.segment.warnings.push_back("profile:large-chapter-table");

    uint64_t complexity=movie.segment.tracks.size()*3+movie.segment.clusters.size()*2+movie.segment.cues.size()+movie.segment.attachments.size()*4+movie.segment.tags.size();

    movie.segment.tag_index["profile.complexity"]=std::to_string(complexity);

}

}
