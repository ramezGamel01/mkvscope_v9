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

std::vector<size_t> parse_lace_sizes(ByteView payload,size_t off,uint8_t flags,Diagnostics& diag){
 std::vector<size_t> sizes;
 uint8_t mode=(flags>>1)&0x3;
 if(mode==0 || !payload.has(off,1)){
 sizes.push_back(payload.size()>off?payload.size()-off:0);
 return sizes;
 }
 uint8_t frames=payload.u8(off++) + 1;
 sizes.resize(frames);

    if(mode==1){
 size_t total=0;
 for(unsigned i=0;i<frames;i++){
 size_t v=0;
 while(payload.has(off,1)){
 uint8_t c=payload.u8(off++);
 v+=c;
 if(c!=255) break;
 }
 sizes[i]=v;
 total+=v;
 }
 if(total<payload.size()-off) sizes.back()=payload.size()-off-total;
 }

    else if(mode==3){
 size_t remain=payload.size()-off;
 for(unsigned i=0;i<frames;i++){
 sizes[i]=remain/frames;
 }
 }

    else {
 size_t remain=payload.size()-off;
 for(unsigned i=0;i<frames;i++) sizes[i]=remain/frames;
 }

    return sizes;
 }

std::vector<BlockFrame> split_laced_block(const BlockFrame& block,Diagnostics& diag){
 std::vector<BlockFrame> out;
 ByteView payload(block.bytes.data(),block.bytes.size());
 auto sizes=parse_lace_sizes(payload,0,block.flags,diag);
 size_t off=(sizes.size()>1)?1:0;
 for(size_t i=0;i<sizes.size();++i){
 BlockFrame f=block;
 f.bytes=payload.vec(off,sizes[i]);
 f.rel_time=(int16_t)(block.rel_time+i);
 out.push_back(std::move(f));
 off+=sizes[i];
 }
 return out;
 }

}
