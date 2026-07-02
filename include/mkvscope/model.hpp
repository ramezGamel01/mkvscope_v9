
#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include "mkvscope/diagnostics.hpp"
namespace mkv {

struct BlockFrame {
 uint32_t track{
};
 int16_t rel_time{
};
 uint8_t flags{
};
 std::vector<uint8_t> bytes;
 uint64_t absolute_time{
};
 uint64_t duration{
};
 uint64_t source_cluster{
};
 }
;
struct CodecPrivate {
 std::vector<uint8_t> data;
 std::string family;
 uint32_t profile{
};
 uint32_t level{
};
 std::vector<std::vector<uint8_t>> parameter_sets;
 }
;
struct SampleEntry {

    std::string codec_id;
 CodecPrivate private_data;
 uint32_t channels{
};
 uint32_t width{
};
 uint32_t height{
};
 uint32_t sample_rate{
};
 bool video{
};
 bool audio{
};

};

struct Track {
 uint32_t number{
};
 uint64_t uid{
};
 uint32_t type{
};
 std::vector<SampleEntry> entries;
 std::vector<BlockFrame> frames;
 std::string name;
 std::map<std::string,std::string> tags;
 double score{
};
 }
;
struct Cluster {
 uint64_t timecode{
};
 uint64_t file_position{
};
 std::vector<BlockFrame> blocks;
 std::vector<uint64_t> referenced_tracks;
 }
;
struct CueTrackPosition {
 uint32_t track{
};
 uint64_t cluster_position{
};
 uint64_t relative_position{
};
 uint64_t resolved_time{
};
 }
;
struct CuePoint {
 uint64_t time{
};
 std::vector<CueTrackPosition> positions;
 }
;
struct SeekEntry {
 std::vector<uint8_t> target_id;
 uint64_t position{
};
 uint64_t resolved_index{
};
 std::string name;
 }
;
struct TagPair {
 std::string name;
 std::string value;
 const char* transient_alias{
};
 }
;
struct ChapterDisplay {
 std::string text;
 std::string language;
 }
;
struct Chapter {
 uint64_t uid{
};
 uint64_t start{
};
 std::vector<ChapterDisplay> displays;
 std::vector<uint32_t> display_refs;
 std::vector<Chapter> children;
 }
;
struct Attachment {
 uint64_t uid{
};
 std::string name;
 std::vector<uint8_t> data;
 std::string probe;
 }
;
struct SegmentInfo {
 uint64_t timecode_scale{
1000000}
; std::string muxing_app;
 std::string writing_app;
 uint64_t duration{
};
 }
;
struct Segment {
 SegmentInfo info;
 std::vector<Track> tracks;
 std::vector<Cluster> clusters;
 std::vector<CuePoint> cues;
 std::vector<SeekEntry> seeks;
 std::vector<TagPair> tags;
 std::vector<Chapter> chapters;
 std::vector<Attachment> attachments;
 std::map<std::string,std::string> tag_index;
 std::vector<std::string> warnings;
 }
;
struct Movie {
 Segment segment;
 Diagnostics diagnostics;
 std::string doc_type;
 uint64_t fingerprint{
};
 }
;
}
