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

std::string clean_utf8(ByteView v){
 std::string s;
 s.reserve(v.size());
 for(size_t i=0;i<v.size();++i){
 unsigned char c=v.u8(i);
 if(c==0) continue;
 if(c<32 && c!='\n' && c!='\t') continue;
 s.push_back(char(c));
 }
 return s;
 }

std::string json_escape(const std::string& s){
 std::string o;
 o.reserve(s.size()+8);
 for(unsigned char c: s){
 switch(c){
 case '"': o+="\\\"";
 break;
 case '\\': o+="\\\\";
 break;
 case '\n': o+="\\n";
 break;
 case '\r': o+="\\r";
 break;
 case '\t': o+="\\t";
 break;
 default: if(c<32){
 char buf[8];
 std::snprintf(buf,sizeof(buf),"\\u%04x",c);
 o+=buf;
 }
 else o.push_back(char(c));
 }
 }
 return o;
 }

std::string lower_ascii(std::string s){
 for(char& c:s) c=char(std::tolower((unsigned char)c));
 return s;
 }

}
