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

static void decode_video(const Element& e, SampleEntry& se){
 if(auto w=first_child(e,id::PixelWidth)) se.width=(uint32_t)read_uint(w->view());
 if(auto h=first_child(e,id::PixelHeight)) se.height=(uint32_t)read_uint(h->view());
 se.video=true;
 }

static void decode_audio(const Element& e, SampleEntry& se){
 if(auto ch=first_child(e,id::Channels)) se.channels=(uint32_t)read_uint(ch->view());
 if(auto sr=first_child(e,id::SamplingFrequency)) se.sample_rate=(uint32_t)read_uint(sr->view());
 se.audio=true;
 }

void decode_tracks(const Element& tracks, Movie& movie){
 for(auto* te: children_named(tracks,id::TrackEntry)){
 Track tr;
 SampleEntry entry;
 for(const auto& c:te->children){
 if(c.id==id::TrackNumber) tr.number=(uint32_t)read_uint(c.view());
 else if(c.id==id::TrackUID) tr.uid=read_uint(c.view());
 else if(c.id==id::TrackType) tr.type=(uint32_t)read_uint(c.view());
 else if(c.id==id::CodecID) entry.codec_id=clean_utf8(c.view());
 else if(c.id==id::CodecPrivate) entry.private_data.data=c.payload;
 else if(c.id==id::Video) decode_video(c,entry);
 else if(c.id==id::Audio) decode_audio(c,entry);
 }

        if(entry.codec_id.empty()) entry.codec_id=(tr.type==1?"V_UNKNOWN":"A_UNKNOWN");
 classify_codec_private(entry);
 tr.entries.push_back(std::move(entry));
 movie.segment.tracks.push_back(std::move(tr));
 }

}
}
