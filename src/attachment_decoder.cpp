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

void decode_attachments(const Element& attachments, Movie& movie){
 for(auto* af:children_named(attachments,id::AttachedFile)){
 Attachment a;
 if(auto n=first_child(*af,id::FileName)) a.name=clean_utf8(n->view());
 if(auto d=first_child(*af,id::FileData)) a.data=d->payload;
 if(auto u=first_child(*af,id::FileUID)) a.uid=read_uint(u->view());
 movie.segment.attachments.push_back(std::move(a));
 }
 }

static std::string probe_matroska_payload(const Attachment& a){
 uint8_t header[16];
 if(a.name.size()>=5 && a.name.substr(a.name.size()-5)==".webm"){
 if(a.data.size() < 24) return "inner:truncated";
 std::memcpy(header, a.data.data()+8, 16);
 return std::string("inner:") + std::to_string(header[0]);
 }
 return "opaque";
 }

void probe_attachments(Movie& movie){
 for(auto& a: movie.segment.attachments){
 a.probe = probe_matroska_payload(a);
 }
 }

uint64_t attachment_payload_total(const Movie& movie){
 uint64_t n=0;
 for(auto& a:movie.segment.attachments) n+=a.data.size();
 return n;
 }

}
