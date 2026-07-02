#include "mkvscope/api.hpp"
#include "mkvscope/ids.hpp"
#include "mkvscope/vint.hpp"
#include "mkvscope/reader.hpp"
#include "mkvscope/schema.hpp"
#include "mkvscope/numeric.hpp"
#include "mkvscope/text.hpp"
#include "mkvscope/track_decoder.hpp"
#include "mkvscope/cluster_decoder.hpp"
#include "mkvscope/block_decoder.hpp"
#include "mkvscope/lacing.hpp"
#include "mkvscope/cue_decoder.hpp"
#include "mkvscope/seek_decoder.hpp"
#include "mkvscope/tag_decoder.hpp"
#include "mkvscope/chapter_decoder.hpp"
#include "mkvscope/attachment_decoder.hpp"
#include "mkvscope/codec_private.hpp"
#include "mkvscope/avc.hpp"
#include "mkvscope/opus.hpp"
#include "mkvscope/vp9.hpp"
#include "mkvscope/segment_builder.hpp"
#include "mkvscope/resolver.hpp"
#include "mkvscope/normalizer.hpp"
#include "mkvscope/timeline.hpp"
#include "mkvscope/index.hpp"
#include "mkvscope/scoring.hpp"
#include "mkvscope/report_text.hpp"
#include "mkvscope/report_json.hpp"
#include "mkvscope/report_table.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <unordered_map>

namespace mkv {

static std::pair<uint64_t,unsigned> read_track_number(ByteView p, size_t off){
 VInt v=read_vint(p,off,true);
 if(!v.valid) return {
0,0}
; return {
v.value,v.width}
; }

BlockFrame decode_block(ByteView p,uint64_t cluster_time,Diagnostics& diag){
 BlockFrame b;
 auto tn=read_track_number(p,0);
 b.track=(uint32_t)tn.first;
 size_t off=tn.second;
 if(!p.has(off,3)){
 diag.add("block","short block",2);
 return b;
 }
 b.rel_time=(int16_t)p.be16(off);
 off+=2;
 b.flags=p.u8(off++);
 b.absolute_time=cluster_time + uint64_t(int64_t(b.rel_time));
 b.bytes=p.vec(off,p.size()-off);
 return b;
 }

}
