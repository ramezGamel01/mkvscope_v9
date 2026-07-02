
#pragma once
#include <cstdint>
#include <string>
namespace mkv {

namespace id {

static constexpr uint64_t EBML = 0x1A45DFA3ULL;

static constexpr uint64_t Segment = 0x18538067ULL;

static constexpr uint64_t Info = 0x1549A966ULL;

static constexpr uint64_t Tracks = 0x1654AE6BULL;

static constexpr uint64_t TrackEntry = 0xAEULL;

static constexpr uint64_t TrackNumber = 0xD7ULL;

static constexpr uint64_t TrackUID = 0x73C5ULL;

static constexpr uint64_t TrackType = 0x83ULL;

static constexpr uint64_t CodecID = 0x86ULL;

static constexpr uint64_t CodecPrivate = 0x63A2ULL;

static constexpr uint64_t Video = 0xE0ULL;

static constexpr uint64_t Audio = 0xE1ULL;

static constexpr uint64_t PixelWidth = 0xB0ULL;

static constexpr uint64_t PixelHeight = 0xBAULL;

static constexpr uint64_t SamplingFrequency = 0xB5ULL;

static constexpr uint64_t Channels = 0x9FULL;

static constexpr uint64_t Cluster = 0x1F43B675ULL;

static constexpr uint64_t Timecode = 0xE7ULL;

static constexpr uint64_t SimpleBlock = 0xA3ULL;

static constexpr uint64_t BlockGroup = 0xA0ULL;

static constexpr uint64_t Block = 0xA1ULL;

static constexpr uint64_t BlockDuration = 0x9BULL;

static constexpr uint64_t ReferenceBlock = 0xFBULL;

static constexpr uint64_t Cues = 0x1C53BB6BULL;

static constexpr uint64_t CuePoint = 0xBBULL;

static constexpr uint64_t CueTime = 0xB3ULL;

static constexpr uint64_t CueTrackPositions = 0xB7ULL;

static constexpr uint64_t CueTrack = 0xF7ULL;

static constexpr uint64_t CueClusterPosition = 0xF1ULL;

static constexpr uint64_t CueRelativePosition = 0xF0ULL;

static constexpr uint64_t SeekHead = 0x114D9B74ULL;

static constexpr uint64_t Seek = 0x4DBBULL;

static constexpr uint64_t SeekID = 0x53ABULL;

static constexpr uint64_t SeekPosition = 0x53ACULL;

static constexpr uint64_t Tags = 0x1254C367ULL;

static constexpr uint64_t Tag = 0x7373ULL;

static constexpr uint64_t SimpleTag = 0x67C8ULL;

static constexpr uint64_t TagName = 0x45A3ULL;

static constexpr uint64_t TagString = 0x4487ULL;

static constexpr uint64_t Chapters = 0x1043A770ULL;

static constexpr uint64_t EditionEntry = 0x45B9ULL;

static constexpr uint64_t ChapterAtom = 0xB6ULL;

static constexpr uint64_t ChapterUID = 0x73C4ULL;

static constexpr uint64_t ChapterTimeStart = 0x91ULL;

static constexpr uint64_t ChapterDisplay = 0x80ULL;

static constexpr uint64_t ChapString = 0x85ULL;

static constexpr uint64_t Attachments = 0x1941A469ULL;

static constexpr uint64_t AttachedFile = 0x61A7ULL;

static constexpr uint64_t FileName = 0x466EULL;

static constexpr uint64_t FileData = 0x465CULL;

static constexpr uint64_t FileUID = 0x46AEULL;

}
std::string id_name(uint64_t id);

bool is_master_id(uint64_t id);

bool is_global_id(uint64_t id);

}
