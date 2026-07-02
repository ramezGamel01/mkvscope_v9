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

std::string id_name(uint64_t x){

    static const std::pair<uint64_t,const char*> names[]={
{id::EBML,"EBML"}
,{
id::Segment,"Segment"}
,{
id::Info,"Info"}
,{
id::Tracks,"Tracks"}
,{
id::TrackEntry,"TrackEntry"}
,{
id::TrackNumber,"TrackNumber"}
,{
id::TrackUID,"TrackUID"}
,{
id::TrackType,"TrackType"}
,{
id::CodecID,"CodecID"}
,{
id::CodecPrivate,"CodecPrivate"}
,{
id::Video,"Video"}
,{
id::Audio,"Audio"}
,{
id::Cluster,"Cluster"}
,{
id::SimpleBlock,"SimpleBlock"}
,{
id::BlockGroup,"BlockGroup"}
,{
id::Block,"Block"}
,{
id::Cues,"Cues"}
,{
id::CuePoint,"CuePoint"}
,{
id::CueTrackPositions,"CueTrackPositions"}
,{
id::SeekHead,"SeekHead"}
,{
id::Seek,"Seek"}
,{
id::Tags,"Tags"}
,{
id::SimpleTag,"SimpleTag"}
,{
id::Chapters,"Chapters"}
,{
id::ChapterAtom,"ChapterAtom"}
,{
id::Attachments,"Attachments"}
,{
id::AttachedFile,"AttachedFile"}
};

    for(auto& p:names) if(p.first==x) return p.second;
 std::ostringstream os;
 os<<"0x"<<std::hex<<x;
 return os.str();

}
bool is_master_id(uint64_t x){
 switch(x){
case id::EBML: case id::Segment: case id::Info: case id::Tracks: case id::TrackEntry: case id::Video: case id::Audio: case id::Cluster: case id::BlockGroup: case id::Cues: case id::CuePoint: case id::CueTrackPositions: case id::SeekHead: case id::Seek: case id::Tags: case id::Tag: case id::SimpleTag: case id::Chapters: case id::EditionEntry: case id::ChapterAtom: case id::ChapterDisplay: case id::Attachments: case id::AttachedFile: return true;
 default: return false;
} }

bool is_global_id(uint64_t x){
 return x==0xEC || x==0xBF;
 }

}
