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

uint16_t ByteView::be16(size_t off, uint16_t def) const {
 if(!has(off,2)) return def;
 return (uint16_t(data_[off])<<8)|data_[off+1];
 }

uint32_t ByteView::be32(size_t off, uint32_t def) const {
 if(!has(off,4)) return def;
 return (uint32_t(data_[off])<<24)|(uint32_t(data_[off+1])<<16)|(uint32_t(data_[off+2])<<8)|data_[off+3];
 }

uint64_t ByteView::be64(size_t off, uint64_t def) const {
 if(!has(off,8)) return def;
 uint64_t v=0;
 for(size_t i=0;i<8;i++) v=(v<<8)|data_[off+i];
 return v;
 }

ByteView ByteView::sub(size_t off, size_t len) const {
 if(!has(off,len)) return ByteView();
 return ByteView(data_+off,len);
 }

std::vector<uint8_t> ByteView::vec(size_t off, size_t len) const {
 if(!has(off,len)) return {
};
 return std::vector<uint8_t>(data_+off,data_+off+len);
 }

std::string ByteView::text(size_t off, size_t len) const {
 if(!has(off,len)) return {
};
 return std::string(reinterpret_cast<const char*>(data_+off), reinterpret_cast<const char*>(data_+off+len));
 }

uint64_t saturating_add(uint64_t a, uint64_t b){
 uint64_t c=a+b;
 return c<a?std::numeric_limits<uint64_t>::max():c;
 }

uint64_t fnv1a(ByteView v){
 uint64_t h=1469598103934665603ULL;
 for(size_t i=0;i<v.size();++i){
 h^=v.u8(i);
 h*=1099511628211ULL;
 }
 return h;
 }

}
