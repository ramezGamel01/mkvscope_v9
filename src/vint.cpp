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

unsigned vint_width(uint8_t first){
 for(unsigned i=0;i<8;i++) if(first & (0x80u>>i)) return i+1;
 return 0;
 }

VInt read_vint(ByteView v,size_t off,bool clear_marker){
 if(off>=v.size()) return {
};
 uint8_t first=v.u8(off);
 unsigned w=vint_width(first);
 if(!w || !v.has(off,w)) return {
};
 uint64_t val= clear_marker ? (first & ((1u<<(8-w))-1u)) : first;
 for(unsigned i=1;i<w;i++) val=(val<<8)|v.u8(off+i);
 uint64_t allones=(w==8)?0x00FFFFFFFFFFFFFFULL:((1ULL<<(7*w))-1ULL);
 return {
val,w,val==allones,true}
; }

VInt read_id(ByteView v,size_t off){
 return read_vint(v,off,false);
 }

std::vector<uint8_t> encode_id(uint64_t id){
 if(id>0xFFFFFF) return {
uint8_t(id>>24),uint8_t(id>>16),uint8_t(id>>8),uint8_t(id)}
; if(id>0xFFFF) return {
uint8_t(id>>16),uint8_t(id>>8),uint8_t(id)}
; if(id>0xFF) return {
uint8_t(id>>8),uint8_t(id)}
; return {
uint8_t(id)}
; }

std::vector<uint8_t> encode_size(uint64_t size){
 if(size<0x7f) return {
uint8_t(0x80|size)}
; if(size<0x3fff) return {
uint8_t(0x40|(size>>8)),uint8_t(size)}
; if(size<0x1fffff) return {
uint8_t(0x20|(size>>16)),uint8_t(size>>8),uint8_t(size)}
; return {
uint8_t(0x10|(size>>24)),uint8_t(size>>16),uint8_t(size>>8),uint8_t(size)}
; }

}
