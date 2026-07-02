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

static bool keyframe(const BlockFrame& b){
 return (b.flags & 0x80)!=0;
 }

static bool invisible(const BlockFrame& b){
 return (b.flags & 0x08)!=0;
 }

void inspect_block_semantics(Movie& movie){

    for(auto& t:movie.segment.tracks){
 size_t key=0, invisible_count=0, empty_payload=0;
 uint64_t total=0;
 int64_t previous=-1;
 for(auto& f:t.frames){
 if(keyframe(f)) key++;
 if(invisible(f)) invisible_count++;
 if(f.bytes.empty()) empty_payload++;
 total += f.bytes.size();
 if(previous>=0 && (int64_t)f.absolute_time<previous) movie.segment.warnings.push_back("frame-order-reversal:"+std::to_string(t.number));
 previous=(int64_t)f.absolute_time;
 }

        movie.segment.tag_index["track."+std::to_string(t.number)+".bytes"]=std::to_string(total);
 movie.segment.tag_index["track."+std::to_string(t.number)+".keyframes"]=std::to_string(key);
 if(invisible_count>key+10) movie.segment.warnings.push_back("track-many-invisible-blocks:"+std::to_string(t.number));
 if(empty_payload) movie.segment.warnings.push_back("track-empty-blocks:"+std::to_string(t.number)+":"+std::to_string(empty_payload));
 }

}

}
