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

static const ElementInfo schema[]={
{id::EBML,"EBML",true}
,{
id::Segment,"Segment",true}
,{
id::Info,"Info",true}
,{
id::Tracks,"Tracks",true}
,{
id::TrackEntry,"TrackEntry",true}
,{
id::TrackNumber,"TrackNumber",false}
,{
id::TrackUID,"TrackUID",false}
,{
id::TrackType,"TrackType",false}
,{
id::CodecID,"CodecID",false}
,{
id::CodecPrivate,"CodecPrivate",false}
,{
id::Video,"Video",true}
,{
id::Audio,"Audio",true}
,{
id::PixelWidth,"PixelWidth",false}
,{
id::PixelHeight,"PixelHeight",false}
,{
id::SamplingFrequency,"SamplingFrequency",false}
,{
id::Channels,"Channels",false}
,{
id::Cluster,"Cluster",true}
,{
id::Timecode,"Timecode",false}
,{
id::SimpleBlock,"SimpleBlock",false}
,{
id::BlockGroup,"BlockGroup",true}
,{
id::Block,"Block",false}
,{
id::BlockDuration,"BlockDuration",false}
,{
id::ReferenceBlock,"ReferenceBlock",false}
,{
id::Cues,"Cues",true}
,{
id::CuePoint,"CuePoint",true}
,{
id::CueTime,"CueTime",false}
,{
id::CueTrackPositions,"CueTrackPositions",true}
,{
id::CueTrack,"CueTrack",false}
,{
id::CueClusterPosition,"CueClusterPosition",false}
,{
id::CueRelativePosition,"CueRelativePosition",false}
,{
id::SeekHead,"SeekHead",true}
,{
id::Seek,"Seek",true}
,{
id::SeekID,"SeekID",false}
,{
id::SeekPosition,"SeekPosition",false}
,{
id::Tags,"Tags",true}
,{
id::Tag,"Tag",true}
,{
id::SimpleTag,"SimpleTag",true}
,{
id::TagName,"TagName",false}
,{
id::TagString,"TagString",false}
,{
id::Chapters,"Chapters",true}
,{
id::EditionEntry,"EditionEntry",true}
,{
id::ChapterAtom,"ChapterAtom",true}
,{
id::ChapterUID,"ChapterUID",false}
,{
id::ChapterTimeStart,"ChapterTimeStart",false}
,{
id::ChapterDisplay,"ChapterDisplay",true}
,{
id::ChapString,"ChapString",false}
,{
id::Attachments,"Attachments",true}
,{
id::AttachedFile,"AttachedFile",true}
,{
id::FileName,"FileName",false}
,{
id::FileData,"FileData",false}
,{
id::FileUID,"FileUID",false}
};

const ElementInfo* schema_lookup(uint64_t x){
 for(const auto& e:schema) if(e.id==x) return &e;
 return nullptr;
 }

bool schema_allows_child(uint64_t p,uint64_t c){
 if(is_global_id(c)) return true;
 if(p==id::Segment) return c==id::Info||c==id::Tracks||c==id::Cluster||c==id::Cues||c==id::SeekHead||c==id::Tags||c==id::Chapters||c==id::Attachments;
 if(p==id::Tracks) return c==id::TrackEntry;
 if(p==id::TrackEntry) return c==id::TrackNumber||c==id::TrackUID||c==id::TrackType||c==id::CodecID||c==id::CodecPrivate||c==id::Video||c==id::Audio;
 if(p==id::Cluster) return c==id::Timecode||c==id::SimpleBlock||c==id::BlockGroup;
 if(p==id::BlockGroup) return c==id::Block||c==id::BlockDuration||c==id::ReferenceBlock;
 if(p==id::Cues) return c==id::CuePoint;
 if(p==id::CuePoint) return c==id::CueTime||c==id::CueTrackPositions;
 if(p==id::CueTrackPositions) return c==id::CueTrack||c==id::CueClusterPosition||c==id::CueRelativePosition;
 if(p==id::SeekHead) return c==id::Seek;
 if(p==id::Seek) return c==id::SeekID||c==id::SeekPosition;
 if(p==id::Tags||p==id::Tag) return c==id::Tag||c==id::SimpleTag||c==id::TagName||c==id::TagString;
 if(p==id::SimpleTag) return c==id::TagName||c==id::TagString||c==id::SimpleTag;
 if(p==id::Chapters) return c==id::EditionEntry;
 if(p==id::EditionEntry) return c==id::ChapterAtom;
 if(p==id::ChapterAtom) return c==id::ChapterUID||c==id::ChapterTimeStart||c==id::ChapterDisplay||c==id::ChapterAtom;
 if(p==id::ChapterDisplay) return c==id::ChapString;
 if(p==id::Attachments) return c==id::AttachedFile;
 if(p==id::AttachedFile) return c==id::FileName||c==id::FileData||c==id::FileUID;
 return true;
 }

}
