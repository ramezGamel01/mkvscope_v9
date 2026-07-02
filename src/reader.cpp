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

void scan_children(ByteView bytes,size_t start,size_t end,unsigned depth,const std::string& path,std::vector<Element>& out,Diagnostics& diag,const ReaderOptions& opts){

    size_t off=start;
 unsigned count=0;
 if(end>bytes.size()) end=bytes.size();

    while(off<end && count++<opts.max_children){
 VInt ident=read_id(bytes,off);
 if(!ident.valid){
 diag.add("reader","invalid EBML identifier",2);
 break;
 }
 size_t size_off=off+ident.width;
 VInt sz=read_vint(bytes,size_off,true);
 if(!sz.valid){
 diag.add("reader","invalid EBML size",2);
 break;
 }
 size_t payload_off=size_off+sz.width;
 if(payload_off>bytes.size()) break;
 uint64_t payload_size=sz.unknown?uint64_t(end-payload_off):sz.value;
 if(payload_size>bytes.size()-payload_off){
 diag.add("reader","element size exceeds parent",2);
 payload_size=bytes.size()-payload_off;
 }

        Element e;
 e.id=ident.value;
 e.size=payload_size;
 e.header_offset=off;
 e.payload_offset=payload_off;
 e.depth=depth;
 e.path=path+"/"+id_name(e.id);
 if(opts.retain_payloads) e.payload=bytes.vec(payload_off,(size_t)payload_size);

        if(is_master_id(e.id) && depth<opts.max_depth){
 ByteView pv=bytes.sub(payload_off,(size_t)payload_size);
 scan_children(pv,0,pv.size(),depth+1,e.path,e.children,diag,opts);
 }

        out.push_back(std::move(e));
 off=payload_off+(size_t)payload_size;
 }

}
Document parse_ebml(ByteView bytes,Diagnostics& diag,ReaderOptions opts){
 Document d;
 d.diagnostics=&diag;
 scan_children(bytes,0,bytes.size(),0,"",d.roots,diag,opts);
 return d;
 }

}
