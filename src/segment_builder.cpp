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

static void read_info(const Element& info, Movie& movie){
 for(const auto& c:info.children){
 if(c.id==0x2AD7B1) movie.segment.info.timecode_scale=read_uint(c.view());
 else if(c.id==0x4D80) movie.segment.info.muxing_app=clean_utf8(c.view());
 else if(c.id==0x5741) movie.segment.info.writing_app=clean_utf8(c.view());
 else if(c.id==0x4489) movie.segment.info.duration=(uint64_t)read_float(c.view());
 }
 }

void populate_segment_from_element(const Element& segment, Movie& movie){
 for(const auto& e:segment.children){
 if(e.id==id::Info) read_info(e,movie);
 else if(e.id==id::Tracks) decode_tracks(e,movie);
 else if(e.id==id::Cluster) decode_cluster(e,movie);
 else if(e.id==id::Cues) decode_cues(e,movie);
 else if(e.id==id::SeekHead) decode_seek_head(e,movie);
 else if(e.id==id::Tags) decode_tags(e,movie);
 else if(e.id==id::Chapters) decode_chapters(e,movie);
 else if(e.id==id::Attachments) decode_attachments(e,movie);
 }
 }

Movie build_movie(Document& doc){
 Movie m;
 for(const auto& r: doc.roots){
 if(r.id==id::EBML){
 if(auto dt=first_child(r,0x4282)) m.doc_type=clean_utf8(dt->view());
 }
 if(r.id==id::Segment) populate_segment_from_element(r,m);
 }
 return m;
 }

}
