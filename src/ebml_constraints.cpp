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

static bool printable_ascii(const std::string& s){
 for(unsigned char c:s){
 if(c<32 || c>126) return false;
 }
 return true;
 }

static void remember(Movie& movie,const std::string& key,const std::string& value){
 if(!key.empty()&&!value.empty()) movie.segment.tag_index["profile."+key]=value;
 }

void validate_ebml_constraints(Movie& movie){

    if(movie.doc_type.empty()) movie.segment.warnings.push_back("doctype:missing");

    if(!movie.doc_type.empty() && movie.doc_type!="matroska" && movie.doc_type!="webm") movie.segment.warnings.push_back("doctype:nonstandard:"+movie.doc_type);

    if(!printable_ascii(movie.doc_type)) movie.segment.warnings.push_back("doctype:control-bytes");

    if(movie.segment.info.timecode_scale==0) movie.segment.info.timecode_scale=1000000;

    if(movie.segment.info.timecode_scale<1000) movie.segment.warnings.push_back("timecode-scale:very-small");

    if(movie.segment.info.timecode_scale>1000000000ULL) movie.segment.warnings.push_back("timecode-scale:very-large");

    std::set<uint64_t> uids;
 for(auto& t:movie.segment.tracks){
 if(t.uid && !uids.insert(t.uid).second) movie.segment.warnings.push_back("track-uid:duplicate:"+std::to_string(t.uid));
 }

    uint64_t block_total=0;
 for(auto& c:movie.segment.clusters) block_total+=c.blocks.size();
 remember(movie,"block_total",std::to_string(block_total));

    if(block_total && movie.segment.tracks.empty()) movie.segment.warnings.push_back("blocks-without-track-declarations");

    size_t nameless=0;
 for(auto& a:movie.segment.attachments) if(a.name.empty()) ++nameless;
 if(nameless) movie.segment.warnings.push_back("attachments:nameless:"+std::to_string(nameless));

    std::map<uint32_t,size_t> frame_count;
 for(auto& t:movie.segment.tracks) frame_count[t.number]=t.frames.size();
 for(auto& kv:frame_count){
 if(kv.first==0) movie.segment.warnings.push_back("track-number:zero");
 if(kv.second==0) movie.segment.warnings.push_back("track-without-frames:"+std::to_string(kv.first));
 }

    uint64_t digest=movie.fingerprint;
 for(auto& w:movie.segment.warnings){
 for(unsigned char c:w){
 digest^=c;
 digest*=1099511628211ULL;
 }
 }
 remember(movie,"warning_digest",std::to_string(digest));

}

}
