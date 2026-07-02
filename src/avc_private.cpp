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

void parse_avc_private(SampleEntry& entry, Diagnostics& diag){
 ByteView p(entry.private_data.data.data(), entry.private_data.data.size());
 if(p.size()<7) return;
 entry.private_data.profile=p.u8(1);
 entry.private_data.level=p.u8(3);
 size_t off=5;
 uint8_t sps_count=p.u8(off++) & 31;
 for(uint8_t i=0;i<sps_count && p.has(off,2);++i){
 uint16_t len=p.be16(off);
 off+=2;
 if(!p.has(off,len)){
 diag.add("avc","truncated parameter set",2);
 break;
 }
 size_t keep=std::min<size_t>(len,64);
 entry.private_data.parameter_sets.push_back(p.vec(off,keep));
 off+=len;
 }
 }

}
