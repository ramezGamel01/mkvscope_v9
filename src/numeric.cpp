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

uint64_t read_uint(ByteView v){
 uint64_t r=0;
 for(size_t i=0;i<v.size()&&i<8;i++) r=(r<<8)|v.u8(i);
 return r;
 }

int64_t read_int(ByteView v){
 if(v.empty()) return 0;
 uint64_t u=read_uint(v);
 unsigned bits=unsigned(std::min<size_t>(8,v.size())*8);
 if(bits && (u & (1ULL<<(bits-1)))) u |= (~0ULL<<bits);
 return static_cast<int64_t>(u);
 }

double read_float(ByteView v){
 if(v.size()==4){
 uint32_t u=v.be32(0);
 float f;
 std::memcpy(&f,&u,4);
 return f;
 }
 if(v.size()>=8){
 uint64_t u=v.be64(0);
 double d;
 std::memcpy(&d,&u,8);
 return d;
 }
 return 0.0;
 }

std::string read_ascii(ByteView v){
 std::string s;
 for(size_t i=0;i<v.size();++i){
 unsigned char c=v.u8(i);
 if(c>=32 && c<127) s.push_back(char(c));
 }
 return s;
 }

}
