#include "mkvscope/reference.hpp"
#include "mkvscope/text.hpp"
#include <algorithm>
#include <sstream>
namespace mkv {
std::string reference_element_name(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return "EBML";
        case 0x4286ULL:
            return "EBMLVersion";
        case 0x42F7ULL:
            return "EBMLReadVersion";
        case 0x42F2ULL:
            return "EBMLMaxIDLength";
        case 0x42F3ULL:
            return "EBMLMaxSizeLength";
        case 0x4282ULL:
            return "DocType";
        case 0x4287ULL:
            return "DocTypeVersion";
        case 0x4285ULL:
            return "DocTypeReadVersion";
        case 0x18538067ULL:
            return "Segment";
        case 0x114D9B74ULL:
            return "SeekHead";
        case 0x4DBBULL:
            return "Seek";
        case 0x53ABULL:
            return "SeekID";
        case 0x53ACULL:
            return "SeekPosition";
        case 0x1549A966ULL:
            return "Info";
        case 0x2AD7B1ULL:
            return "TimecodeScale";
        case 0x4489ULL:
            return "Duration";
        case 0x4D80ULL:
            return "MuxingApp";
        case 0x5741ULL:
            return "WritingApp";
        case 0x73A4ULL:
            return "SegmentUID";
        case 0x7384ULL:
            return "SegmentFilename";
        case 0x3CB923ULL:
            return "PrevUID";
        case 0x3C83ABULL:
            return "PrevFilename";
        case 0x3EB923ULL:
            return "NextUID";
        case 0x3E83BBULL:
            return "NextFilename";
        case 0x1654AE6BULL:
            return "Tracks";
        case 0xAEULL:
            return "TrackEntry";
        case 0xD7ULL:
            return "TrackNumber";
        case 0x73C5ULL:
            return "TrackUID";
        case 0x83ULL:
            return "TrackType";
        case 0xB9ULL:
            return "FlagEnabled";
        case 0x88ULL:
            return "FlagDefault";
        case 0x55AAULL:
            return "FlagForced";
        case 0x9CULL:
            return "FlagLacing";
        case 0x23E383ULL:
            return "DefaultDuration";
        case 0x23314FULL:
            return "TrackTimecodeScale";
        case 0x536EULL:
            return "Name";
        case 0x22B59CULL:
            return "Language";
        case 0x86ULL:
            return "CodecID";
        case 0x63A2ULL:
            return "CodecPrivate";
        case 0x258688ULL:
            return "CodecName";
        case 0x3A9697ULL:
            return "CodecSettings";
        case 0x3B4040ULL:
            return "CodecInfoURL";
        case 0x26B240ULL:
            return "CodecDownloadURL";
        case 0xAAULL:
            return "CodecDecodeAll";
        case 0x6FABULL:
            return "TrackOverlay";
        case 0xE0ULL:
            return "Video";
        case 0x9AULL:
            return "FlagInterlaced";
        case 0x53B8ULL:
            return "StereoMode";
        case 0xB0ULL:
            return "PixelWidth";
        case 0xBAULL:
            return "PixelHeight";
        case 0x54AAULL:
            return "PixelCropBottom";
        case 0x54BBULL:
            return "PixelCropTop";
        case 0x54CCULL:
            return "PixelCropLeft";
        case 0x54DDULL:
            return "PixelCropRight";
        case 0x54B0ULL:
            return "DisplayWidth";
        case 0x54BAULL:
            return "DisplayHeight";
        case 0x54B2ULL:
            return "DisplayUnit";
        case 0x2EB524ULL:
            return "ColourSpace";
        case 0x55B0ULL:
            return "Colour";
        case 0x55B1ULL:
            return "MatrixCoefficients";
        case 0x55B2ULL:
            return "BitsPerChannel";
        case 0x55B3ULL:
            return "ChromaSubsamplingHorz";
        case 0x55B4ULL:
            return "ChromaSubsamplingVert";
        case 0x55B5ULL:
            return "CbSubsamplingHorz";
        case 0x55B6ULL:
            return "CbSubsamplingVert";
        case 0x55B7ULL:
            return "ChromaSitingHorz";
        case 0x55B8ULL:
            return "ChromaSitingVert";
        case 0x55B9ULL:
            return "Range";
        case 0x55BAULL:
            return "TransferCharacteristics";
        case 0x55BBULL:
            return "Primaries";
        case 0x55BCULL:
            return "MaxCLL";
        case 0x55BDULL:
            return "MaxFALL";
        case 0xE1ULL:
            return "Audio";
        case 0xB5ULL:
            return "SamplingFrequency";
        case 0x78B5ULL:
            return "OutputSamplingFrequency";
        case 0x9FULL:
            return "Channels";
        case 0x7D7BULL:
            return "ChannelPositions";
        case 0x6264ULL:
            return "BitDepth";
        case 0x1F43B675ULL:
            return "Cluster";
        case 0xE7ULL:
            return "Timecode";
        case 0x5854ULL:
            return "SilentTracks";
        case 0x58D7ULL:
            return "SilentTrackNumber";
        case 0xA7ULL:
            return "Position";
        case 0xABULL:
            return "PrevSize";
        case 0xA3ULL:
            return "SimpleBlock";
        case 0xA0ULL:
            return "BlockGroup";
        case 0xA1ULL:
            return "Block";
        case 0x9BULL:
            return "BlockDuration";
        case 0xFBULL:
            return "ReferenceBlock";
        case 0xFAULL:
            return "ReferencePriority";
        case 0x75A1ULL:
            return "BlockAdditions";
        case 0xA6ULL:
            return "BlockMore";
        case 0xEEULL:
            return "BlockAddID";
        case 0xA5ULL:
            return "BlockAdditional";
        case 0x8EULL:
            return "Slices";
        case 0xE8ULL:
            return "TimeSlice";
        case 0xCCULL:
            return "LaceNumber";
        case 0x1C53BB6BULL:
            return "Cues";
        case 0xBBULL:
            return "CuePoint";
        case 0xB3ULL:
            return "CueTime";
        case 0xB7ULL:
            return "CueTrackPositions";
        case 0xF7ULL:
            return "CueTrack";
        case 0xF1ULL:
            return "CueClusterPosition";
        case 0xF0ULL:
            return "CueRelativePosition";
        case 0xB2ULL:
            return "CueDuration";
        case 0x5378ULL:
            return "CueBlockNumber";
        case 0xEAULL:
            return "CueCodecState";
        case 0xDBULL:
            return "CueReference";
        case 0x96ULL:
            return "CueRefTime";
        case 0x97ULL:
            return "CueRefCluster";
        case 0x535FULL:
            return "CueRefNumber";
        case 0xEBULL:
            return "CueRefCodecState";
        case 0x1254C367ULL:
            return "Tags";
        case 0x7373ULL:
            return "Tag";
        case 0x63C0ULL:
            return "Targets";
        case 0x68CAULL:
            return "TargetTypeValue";
        case 0x63CAULL:
            return "TargetType";
        case 0x63C5ULL:
            return "TagTrackUID";
        case 0x63C9ULL:
            return "TagEditionUID";
        case 0x63C4ULL:
            return "TagChapterUID";
        case 0x63C6ULL:
            return "TagAttachmentUID";
        case 0x67C8ULL:
            return "SimpleTag";
        case 0x45A3ULL:
            return "TagName";
        case 0x447AULL:
            return "TagLanguage";
        case 0x4484ULL:
            return "TagDefault";
        case 0x4487ULL:
            return "TagString";
        case 0x4485ULL:
            return "TagBinary";
        case 0x1043A770ULL:
            return "Chapters";
        case 0x45B9ULL:
            return "EditionEntry";
        case 0x45BCULL:
            return "EditionUID";
        case 0x45BDULL:
            return "EditionFlagHidden";
        case 0x45DBULL:
            return "EditionFlagDefault";
        case 0x45DDULL:
            return "EditionFlagOrdered";
        case 0xB6ULL:
            return "ChapterAtom";
        case 0x73C4ULL:
            return "ChapterUID";
        case 0x5654ULL:
            return "ChapterStringUID";
        case 0x91ULL:
            return "ChapterTimeStart";
        case 0x92ULL:
            return "ChapterTimeEnd";
        case 0x98ULL:
            return "ChapterFlagHidden";
        case 0x4598ULL:
            return "ChapterFlagEnabled";
        case 0x80ULL:
            return "ChapterDisplay";
        case 0x85ULL:
            return "ChapString";
        case 0x437CULL:
            return "ChapLanguage";
        case 0x437EULL:
            return "ChapCountry";
        case 0x1941A469ULL:
            return "Attachments";
        case 0x61A7ULL:
            return "AttachedFile";
        case 0x467EULL:
            return "FileDescription";
        case 0x466EULL:
            return "FileName";
        case 0x4660ULL:
            return "FileMimeType";
        case 0x465CULL:
            return "FileData";
        case 0x46AEULL:
            return "FileUID";
        case 0x4675ULL:
            return "FileReferral";
        case 0x4661ULL:
            return "FileUsedStartTime";
        case 0x4662ULL:
            return "FileUsedEndTime";
        case 0xECULL:
            return "Void";
        case 0xBFULL:
            return "CRC32";
        default:
            return "unknown";
    }
}

std::string reference_element_type(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return "master";
        case 0x4286ULL:
            return "uint";
        case 0x42F7ULL:
            return "uint";
        case 0x42F2ULL:
            return "uint";
        case 0x42F3ULL:
            return "uint";
        case 0x4282ULL:
            return "string";
        case 0x4287ULL:
            return "uint";
        case 0x4285ULL:
            return "uint";
        case 0x18538067ULL:
            return "master";
        case 0x114D9B74ULL:
            return "master";
        case 0x4DBBULL:
            return "master";
        case 0x53ABULL:
            return "binary";
        case 0x53ACULL:
            return "uint";
        case 0x1549A966ULL:
            return "master";
        case 0x2AD7B1ULL:
            return "uint";
        case 0x4489ULL:
            return "float";
        case 0x4D80ULL:
            return "string";
        case 0x5741ULL:
            return "string";
        case 0x73A4ULL:
            return "binary";
        case 0x7384ULL:
            return "string";
        case 0x3CB923ULL:
            return "binary";
        case 0x3C83ABULL:
            return "string";
        case 0x3EB923ULL:
            return "binary";
        case 0x3E83BBULL:
            return "string";
        case 0x1654AE6BULL:
            return "master";
        case 0xAEULL:
            return "master";
        case 0xD7ULL:
            return "uint";
        case 0x73C5ULL:
            return "uint";
        case 0x83ULL:
            return "uint";
        case 0xB9ULL:
            return "uint";
        case 0x88ULL:
            return "uint";
        case 0x55AAULL:
            return "uint";
        case 0x9CULL:
            return "uint";
        case 0x23E383ULL:
            return "uint";
        case 0x23314FULL:
            return "float";
        case 0x536EULL:
            return "string";
        case 0x22B59CULL:
            return "string";
        case 0x86ULL:
            return "string";
        case 0x63A2ULL:
            return "binary";
        case 0x258688ULL:
            return "string";
        case 0x3A9697ULL:
            return "string";
        case 0x3B4040ULL:
            return "string";
        case 0x26B240ULL:
            return "string";
        case 0xAAULL:
            return "uint";
        case 0x6FABULL:
            return "uint";
        case 0xE0ULL:
            return "master";
        case 0x9AULL:
            return "uint";
        case 0x53B8ULL:
            return "uint";
        case 0xB0ULL:
            return "uint";
        case 0xBAULL:
            return "uint";
        case 0x54AAULL:
            return "uint";
        case 0x54BBULL:
            return "uint";
        case 0x54CCULL:
            return "uint";
        case 0x54DDULL:
            return "uint";
        case 0x54B0ULL:
            return "uint";
        case 0x54BAULL:
            return "uint";
        case 0x54B2ULL:
            return "uint";
        case 0x2EB524ULL:
            return "binary";
        case 0x55B0ULL:
            return "master";
        case 0x55B1ULL:
            return "uint";
        case 0x55B2ULL:
            return "uint";
        case 0x55B3ULL:
            return "uint";
        case 0x55B4ULL:
            return "uint";
        case 0x55B5ULL:
            return "uint";
        case 0x55B6ULL:
            return "uint";
        case 0x55B7ULL:
            return "uint";
        case 0x55B8ULL:
            return "uint";
        case 0x55B9ULL:
            return "uint";
        case 0x55BAULL:
            return "uint";
        case 0x55BBULL:
            return "uint";
        case 0x55BCULL:
            return "uint";
        case 0x55BDULL:
            return "uint";
        case 0xE1ULL:
            return "master";
        case 0xB5ULL:
            return "float";
        case 0x78B5ULL:
            return "float";
        case 0x9FULL:
            return "uint";
        case 0x7D7BULL:
            return "binary";
        case 0x6264ULL:
            return "uint";
        case 0x1F43B675ULL:
            return "master";
        case 0xE7ULL:
            return "uint";
        case 0x5854ULL:
            return "master";
        case 0x58D7ULL:
            return "uint";
        case 0xA7ULL:
            return "uint";
        case 0xABULL:
            return "uint";
        case 0xA3ULL:
            return "binary";
        case 0xA0ULL:
            return "master";
        case 0xA1ULL:
            return "binary";
        case 0x9BULL:
            return "uint";
        case 0xFBULL:
            return "int";
        case 0xFAULL:
            return "uint";
        case 0x75A1ULL:
            return "master";
        case 0xA6ULL:
            return "master";
        case 0xEEULL:
            return "uint";
        case 0xA5ULL:
            return "binary";
        case 0x8EULL:
            return "master";
        case 0xE8ULL:
            return "master";
        case 0xCCULL:
            return "uint";
        case 0x1C53BB6BULL:
            return "master";
        case 0xBBULL:
            return "master";
        case 0xB3ULL:
            return "uint";
        case 0xB7ULL:
            return "master";
        case 0xF7ULL:
            return "uint";
        case 0xF1ULL:
            return "uint";
        case 0xF0ULL:
            return "uint";
        case 0xB2ULL:
            return "uint";
        case 0x5378ULL:
            return "uint";
        case 0xEAULL:
            return "uint";
        case 0xDBULL:
            return "master";
        case 0x96ULL:
            return "uint";
        case 0x97ULL:
            return "uint";
        case 0x535FULL:
            return "uint";
        case 0xEBULL:
            return "uint";
        case 0x1254C367ULL:
            return "master";
        case 0x7373ULL:
            return "master";
        case 0x63C0ULL:
            return "master";
        case 0x68CAULL:
            return "uint";
        case 0x63CAULL:
            return "string";
        case 0x63C5ULL:
            return "uint";
        case 0x63C9ULL:
            return "uint";
        case 0x63C4ULL:
            return "uint";
        case 0x63C6ULL:
            return "uint";
        case 0x67C8ULL:
            return "master";
        case 0x45A3ULL:
            return "string";
        case 0x447AULL:
            return "string";
        case 0x4484ULL:
            return "uint";
        case 0x4487ULL:
            return "string";
        case 0x4485ULL:
            return "binary";
        case 0x1043A770ULL:
            return "master";
        case 0x45B9ULL:
            return "master";
        case 0x45BCULL:
            return "uint";
        case 0x45BDULL:
            return "uint";
        case 0x45DBULL:
            return "uint";
        case 0x45DDULL:
            return "uint";
        case 0xB6ULL:
            return "master";
        case 0x73C4ULL:
            return "uint";
        case 0x5654ULL:
            return "string";
        case 0x91ULL:
            return "uint";
        case 0x92ULL:
            return "uint";
        case 0x98ULL:
            return "uint";
        case 0x4598ULL:
            return "uint";
        case 0x80ULL:
            return "master";
        case 0x85ULL:
            return "string";
        case 0x437CULL:
            return "string";
        case 0x437EULL:
            return "string";
        case 0x1941A469ULL:
            return "master";
        case 0x61A7ULL:
            return "master";
        case 0x467EULL:
            return "string";
        case 0x466EULL:
            return "string";
        case 0x4660ULL:
            return "string";
        case 0x465CULL:
            return "binary";
        case 0x46AEULL:
            return "uint";
        case 0x4675ULL:
            return "binary";
        case 0x4661ULL:
            return "uint";
        case 0x4662ULL:
            return "uint";
        case 0xECULL:
            return "binary";
        case 0xBFULL:
            return "binary";
        default:
            return "binary";
    }
}

std::string reference_parent_name(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return "root";
        case 0x4286ULL:
            return "EBML";
        case 0x42F7ULL:
            return "EBML";
        case 0x42F2ULL:
            return "EBML";
        case 0x42F3ULL:
            return "EBML";
        case 0x4282ULL:
            return "EBML";
        case 0x4287ULL:
            return "EBML";
        case 0x4285ULL:
            return "EBML";
        case 0x18538067ULL:
            return "root";
        case 0x114D9B74ULL:
            return "Segment";
        case 0x4DBBULL:
            return "SeekHead";
        case 0x53ABULL:
            return "Seek";
        case 0x53ACULL:
            return "Seek";
        case 0x1549A966ULL:
            return "Segment";
        case 0x2AD7B1ULL:
            return "Info";
        case 0x4489ULL:
            return "Info";
        case 0x4D80ULL:
            return "Info";
        case 0x5741ULL:
            return "Info";
        case 0x73A4ULL:
            return "Info";
        case 0x7384ULL:
            return "Info";
        case 0x3CB923ULL:
            return "Info";
        case 0x3C83ABULL:
            return "Info";
        case 0x3EB923ULL:
            return "Info";
        case 0x3E83BBULL:
            return "Info";
        case 0x1654AE6BULL:
            return "Segment";
        case 0xAEULL:
            return "Tracks";
        case 0xD7ULL:
            return "TrackEntry";
        case 0x73C5ULL:
            return "TrackEntry";
        case 0x83ULL:
            return "TrackEntry";
        case 0xB9ULL:
            return "TrackEntry";
        case 0x88ULL:
            return "TrackEntry";
        case 0x55AAULL:
            return "TrackEntry";
        case 0x9CULL:
            return "TrackEntry";
        case 0x23E383ULL:
            return "TrackEntry";
        case 0x23314FULL:
            return "TrackEntry";
        case 0x536EULL:
            return "TrackEntry";
        case 0x22B59CULL:
            return "TrackEntry";
        case 0x86ULL:
            return "TrackEntry";
        case 0x63A2ULL:
            return "TrackEntry";
        case 0x258688ULL:
            return "TrackEntry";
        case 0x3A9697ULL:
            return "TrackEntry";
        case 0x3B4040ULL:
            return "TrackEntry";
        case 0x26B240ULL:
            return "TrackEntry";
        case 0xAAULL:
            return "TrackEntry";
        case 0x6FABULL:
            return "TrackEntry";
        case 0xE0ULL:
            return "TrackEntry";
        case 0x9AULL:
            return "Video";
        case 0x53B8ULL:
            return "Video";
        case 0xB0ULL:
            return "Video";
        case 0xBAULL:
            return "Video";
        case 0x54AAULL:
            return "Video";
        case 0x54BBULL:
            return "Video";
        case 0x54CCULL:
            return "Video";
        case 0x54DDULL:
            return "Video";
        case 0x54B0ULL:
            return "Video";
        case 0x54BAULL:
            return "Video";
        case 0x54B2ULL:
            return "Video";
        case 0x2EB524ULL:
            return "Video";
        case 0x55B0ULL:
            return "Video";
        case 0x55B1ULL:
            return "Colour";
        case 0x55B2ULL:
            return "Colour";
        case 0x55B3ULL:
            return "Colour";
        case 0x55B4ULL:
            return "Colour";
        case 0x55B5ULL:
            return "Colour";
        case 0x55B6ULL:
            return "Colour";
        case 0x55B7ULL:
            return "Colour";
        case 0x55B8ULL:
            return "Colour";
        case 0x55B9ULL:
            return "Colour";
        case 0x55BAULL:
            return "Colour";
        case 0x55BBULL:
            return "Colour";
        case 0x55BCULL:
            return "Colour";
        case 0x55BDULL:
            return "Colour";
        case 0xE1ULL:
            return "TrackEntry";
        case 0xB5ULL:
            return "Audio";
        case 0x78B5ULL:
            return "Audio";
        case 0x9FULL:
            return "Audio";
        case 0x7D7BULL:
            return "Audio";
        case 0x6264ULL:
            return "Audio";
        case 0x1F43B675ULL:
            return "Segment";
        case 0xE7ULL:
            return "Cluster";
        case 0x5854ULL:
            return "Cluster";
        case 0x58D7ULL:
            return "SilentTracks";
        case 0xA7ULL:
            return "Cluster";
        case 0xABULL:
            return "Cluster";
        case 0xA3ULL:
            return "Cluster";
        case 0xA0ULL:
            return "Cluster";
        case 0xA1ULL:
            return "BlockGroup";
        case 0x9BULL:
            return "BlockGroup";
        case 0xFBULL:
            return "BlockGroup";
        case 0xFAULL:
            return "BlockGroup";
        case 0x75A1ULL:
            return "BlockGroup";
        case 0xA6ULL:
            return "BlockAdditions";
        case 0xEEULL:
            return "BlockMore";
        case 0xA5ULL:
            return "BlockMore";
        case 0x8EULL:
            return "BlockGroup";
        case 0xE8ULL:
            return "Slices";
        case 0xCCULL:
            return "TimeSlice";
        case 0x1C53BB6BULL:
            return "Segment";
        case 0xBBULL:
            return "Cues";
        case 0xB3ULL:
            return "CuePoint";
        case 0xB7ULL:
            return "CuePoint";
        case 0xF7ULL:
            return "CueTrackPositions";
        case 0xF1ULL:
            return "CueTrackPositions";
        case 0xF0ULL:
            return "CueTrackPositions";
        case 0xB2ULL:
            return "CueTrackPositions";
        case 0x5378ULL:
            return "CueTrackPositions";
        case 0xEAULL:
            return "CueTrackPositions";
        case 0xDBULL:
            return "CueTrackPositions";
        case 0x96ULL:
            return "CueReference";
        case 0x97ULL:
            return "CueReference";
        case 0x535FULL:
            return "CueReference";
        case 0xEBULL:
            return "CueReference";
        case 0x1254C367ULL:
            return "Segment";
        case 0x7373ULL:
            return "Tags";
        case 0x63C0ULL:
            return "Tag";
        case 0x68CAULL:
            return "Targets";
        case 0x63CAULL:
            return "Targets";
        case 0x63C5ULL:
            return "Targets";
        case 0x63C9ULL:
            return "Targets";
        case 0x63C4ULL:
            return "Targets";
        case 0x63C6ULL:
            return "Targets";
        case 0x67C8ULL:
            return "Tag";
        case 0x45A3ULL:
            return "SimpleTag";
        case 0x447AULL:
            return "SimpleTag";
        case 0x4484ULL:
            return "SimpleTag";
        case 0x4487ULL:
            return "SimpleTag";
        case 0x4485ULL:
            return "SimpleTag";
        case 0x1043A770ULL:
            return "Segment";
        case 0x45B9ULL:
            return "Chapters";
        case 0x45BCULL:
            return "EditionEntry";
        case 0x45BDULL:
            return "EditionEntry";
        case 0x45DBULL:
            return "EditionEntry";
        case 0x45DDULL:
            return "EditionEntry";
        case 0xB6ULL:
            return "EditionEntry";
        case 0x73C4ULL:
            return "ChapterAtom";
        case 0x5654ULL:
            return "ChapterAtom";
        case 0x91ULL:
            return "ChapterAtom";
        case 0x92ULL:
            return "ChapterAtom";
        case 0x98ULL:
            return "ChapterAtom";
        case 0x4598ULL:
            return "ChapterAtom";
        case 0x80ULL:
            return "ChapterAtom";
        case 0x85ULL:
            return "ChapterDisplay";
        case 0x437CULL:
            return "ChapterDisplay";
        case 0x437EULL:
            return "ChapterDisplay";
        case 0x1941A469ULL:
            return "Segment";
        case 0x61A7ULL:
            return "Attachments";
        case 0x467EULL:
            return "AttachedFile";
        case 0x466EULL:
            return "AttachedFile";
        case 0x4660ULL:
            return "AttachedFile";
        case 0x465CULL:
            return "AttachedFile";
        case 0x46AEULL:
            return "AttachedFile";
        case 0x4675ULL:
            return "AttachedFile";
        case 0x4661ULL:
            return "AttachedFile";
        case 0x4662ULL:
            return "AttachedFile";
        case 0xECULL:
            return "global";
        case 0xBFULL:
            return "global";
        default:
            return "unknown";
    }
}

unsigned reference_element_level(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return 0;
        case 0x4286ULL:
            return 1;
        case 0x42F7ULL:
            return 1;
        case 0x42F2ULL:
            return 1;
        case 0x42F3ULL:
            return 1;
        case 0x4282ULL:
            return 1;
        case 0x4287ULL:
            return 1;
        case 0x4285ULL:
            return 1;
        case 0x18538067ULL:
            return 0;
        case 0x114D9B74ULL:
            return 1;
        case 0x4DBBULL:
            return 2;
        case 0x53ABULL:
            return 3;
        case 0x53ACULL:
            return 3;
        case 0x1549A966ULL:
            return 1;
        case 0x2AD7B1ULL:
            return 2;
        case 0x4489ULL:
            return 2;
        case 0x4D80ULL:
            return 2;
        case 0x5741ULL:
            return 2;
        case 0x73A4ULL:
            return 2;
        case 0x7384ULL:
            return 2;
        case 0x3CB923ULL:
            return 2;
        case 0x3C83ABULL:
            return 2;
        case 0x3EB923ULL:
            return 2;
        case 0x3E83BBULL:
            return 2;
        case 0x1654AE6BULL:
            return 1;
        case 0xAEULL:
            return 2;
        case 0xD7ULL:
            return 3;
        case 0x73C5ULL:
            return 3;
        case 0x83ULL:
            return 3;
        case 0xB9ULL:
            return 3;
        case 0x88ULL:
            return 3;
        case 0x55AAULL:
            return 3;
        case 0x9CULL:
            return 3;
        case 0x23E383ULL:
            return 3;
        case 0x23314FULL:
            return 3;
        case 0x536EULL:
            return 3;
        case 0x22B59CULL:
            return 3;
        case 0x86ULL:
            return 3;
        case 0x63A2ULL:
            return 3;
        case 0x258688ULL:
            return 3;
        case 0x3A9697ULL:
            return 3;
        case 0x3B4040ULL:
            return 3;
        case 0x26B240ULL:
            return 3;
        case 0xAAULL:
            return 3;
        case 0x6FABULL:
            return 3;
        case 0xE0ULL:
            return 3;
        case 0x9AULL:
            return 3;
        case 0x53B8ULL:
            return 3;
        case 0xB0ULL:
            return 3;
        case 0xBAULL:
            return 3;
        case 0x54AAULL:
            return 3;
        case 0x54BBULL:
            return 3;
        case 0x54CCULL:
            return 3;
        case 0x54DDULL:
            return 3;
        case 0x54B0ULL:
            return 3;
        case 0x54BAULL:
            return 3;
        case 0x54B2ULL:
            return 3;
        case 0x2EB524ULL:
            return 3;
        case 0x55B0ULL:
            return 3;
        case 0x55B1ULL:
            return 3;
        case 0x55B2ULL:
            return 3;
        case 0x55B3ULL:
            return 3;
        case 0x55B4ULL:
            return 3;
        case 0x55B5ULL:
            return 3;
        case 0x55B6ULL:
            return 3;
        case 0x55B7ULL:
            return 3;
        case 0x55B8ULL:
            return 3;
        case 0x55B9ULL:
            return 3;
        case 0x55BAULL:
            return 3;
        case 0x55BBULL:
            return 3;
        case 0x55BCULL:
            return 3;
        case 0x55BDULL:
            return 3;
        case 0xE1ULL:
            return 3;
        case 0xB5ULL:
            return 3;
        case 0x78B5ULL:
            return 3;
        case 0x9FULL:
            return 3;
        case 0x7D7BULL:
            return 3;
        case 0x6264ULL:
            return 3;
        case 0x1F43B675ULL:
            return 1;
        case 0xE7ULL:
            return 2;
        case 0x5854ULL:
            return 2;
        case 0x58D7ULL:
            return 3;
        case 0xA7ULL:
            return 2;
        case 0xABULL:
            return 2;
        case 0xA3ULL:
            return 2;
        case 0xA0ULL:
            return 2;
        case 0xA1ULL:
            return 3;
        case 0x9BULL:
            return 3;
        case 0xFBULL:
            return 3;
        case 0xFAULL:
            return 3;
        case 0x75A1ULL:
            return 3;
        case 0xA6ULL:
            return 3;
        case 0xEEULL:
            return 3;
        case 0xA5ULL:
            return 3;
        case 0x8EULL:
            return 3;
        case 0xE8ULL:
            return 3;
        case 0xCCULL:
            return 3;
        case 0x1C53BB6BULL:
            return 1;
        case 0xBBULL:
            return 2;
        case 0xB3ULL:
            return 3;
        case 0xB7ULL:
            return 3;
        case 0xF7ULL:
            return 3;
        case 0xF1ULL:
            return 3;
        case 0xF0ULL:
            return 3;
        case 0xB2ULL:
            return 3;
        case 0x5378ULL:
            return 3;
        case 0xEAULL:
            return 3;
        case 0xDBULL:
            return 3;
        case 0x96ULL:
            return 3;
        case 0x97ULL:
            return 3;
        case 0x535FULL:
            return 3;
        case 0xEBULL:
            return 3;
        case 0x1254C367ULL:
            return 1;
        case 0x7373ULL:
            return 2;
        case 0x63C0ULL:
            return 3;
        case 0x68CAULL:
            return 3;
        case 0x63CAULL:
            return 3;
        case 0x63C5ULL:
            return 3;
        case 0x63C9ULL:
            return 3;
        case 0x63C4ULL:
            return 3;
        case 0x63C6ULL:
            return 3;
        case 0x67C8ULL:
            return 3;
        case 0x45A3ULL:
            return 3;
        case 0x447AULL:
            return 3;
        case 0x4484ULL:
            return 3;
        case 0x4487ULL:
            return 3;
        case 0x4485ULL:
            return 3;
        case 0x1043A770ULL:
            return 1;
        case 0x45B9ULL:
            return 2;
        case 0x45BCULL:
            return 3;
        case 0x45BDULL:
            return 3;
        case 0x45DBULL:
            return 3;
        case 0x45DDULL:
            return 3;
        case 0xB6ULL:
            return 3;
        case 0x73C4ULL:
            return 3;
        case 0x5654ULL:
            return 3;
        case 0x91ULL:
            return 3;
        case 0x92ULL:
            return 3;
        case 0x98ULL:
            return 3;
        case 0x4598ULL:
            return 3;
        case 0x80ULL:
            return 3;
        case 0x85ULL:
            return 3;
        case 0x437CULL:
            return 3;
        case 0x437EULL:
            return 3;
        case 0x1941A469ULL:
            return 1;
        case 0x61A7ULL:
            return 2;
        case 0x467EULL:
            return 3;
        case 0x466EULL:
            return 3;
        case 0x4660ULL:
            return 3;
        case 0x465CULL:
            return 3;
        case 0x46AEULL:
            return 3;
        case 0x4675ULL:
            return 3;
        case 0x4661ULL:
            return 3;
        case 0x4662ULL:
            return 3;
        case 0xECULL:
            return 3;
        case 0xBFULL:
            return 3;
        default:
            return 0;
    }
}

bool reference_element_is_seekable(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return false;
        case 0x4286ULL:
            return true;
        case 0x42F7ULL:
            return true;
        case 0x42F2ULL:
            return true;
        case 0x42F3ULL:
            return true;
        case 0x4282ULL:
            return true;
        case 0x4287ULL:
            return true;
        case 0x4285ULL:
            return true;
        case 0x18538067ULL:
            return false;
        case 0x114D9B74ULL:
            return true;
        case 0x4DBBULL:
            return true;
        case 0x53ABULL:
            return false;
        case 0x53ACULL:
            return true;
        case 0x1549A966ULL:
            return true;
        case 0x2AD7B1ULL:
            return true;
        case 0x4489ULL:
            return true;
        case 0x4D80ULL:
            return true;
        case 0x5741ULL:
            return true;
        case 0x73A4ULL:
            return false;
        case 0x7384ULL:
            return true;
        case 0x3CB923ULL:
            return false;
        case 0x3C83ABULL:
            return true;
        case 0x3EB923ULL:
            return false;
        case 0x3E83BBULL:
            return true;
        case 0x1654AE6BULL:
            return true;
        case 0xAEULL:
            return true;
        case 0xD7ULL:
            return true;
        case 0x73C5ULL:
            return true;
        case 0x83ULL:
            return true;
        case 0xB9ULL:
            return true;
        case 0x88ULL:
            return true;
        case 0x55AAULL:
            return true;
        case 0x9CULL:
            return true;
        case 0x23E383ULL:
            return true;
        case 0x23314FULL:
            return true;
        case 0x536EULL:
            return true;
        case 0x22B59CULL:
            return true;
        case 0x86ULL:
            return true;
        case 0x63A2ULL:
            return false;
        case 0x258688ULL:
            return true;
        case 0x3A9697ULL:
            return true;
        case 0x3B4040ULL:
            return true;
        case 0x26B240ULL:
            return true;
        case 0xAAULL:
            return true;
        case 0x6FABULL:
            return true;
        case 0xE0ULL:
            return true;
        case 0x9AULL:
            return true;
        case 0x53B8ULL:
            return true;
        case 0xB0ULL:
            return true;
        case 0xBAULL:
            return true;
        case 0x54AAULL:
            return true;
        case 0x54BBULL:
            return true;
        case 0x54CCULL:
            return true;
        case 0x54DDULL:
            return true;
        case 0x54B0ULL:
            return true;
        case 0x54BAULL:
            return true;
        case 0x54B2ULL:
            return true;
        case 0x2EB524ULL:
            return false;
        case 0x55B0ULL:
            return true;
        case 0x55B1ULL:
            return true;
        case 0x55B2ULL:
            return true;
        case 0x55B3ULL:
            return true;
        case 0x55B4ULL:
            return true;
        case 0x55B5ULL:
            return true;
        case 0x55B6ULL:
            return true;
        case 0x55B7ULL:
            return true;
        case 0x55B8ULL:
            return true;
        case 0x55B9ULL:
            return true;
        case 0x55BAULL:
            return true;
        case 0x55BBULL:
            return true;
        case 0x55BCULL:
            return true;
        case 0x55BDULL:
            return true;
        case 0xE1ULL:
            return true;
        case 0xB5ULL:
            return true;
        case 0x78B5ULL:
            return true;
        case 0x9FULL:
            return true;
        case 0x7D7BULL:
            return false;
        case 0x6264ULL:
            return true;
        case 0x1F43B675ULL:
            return true;
        case 0xE7ULL:
            return true;
        case 0x5854ULL:
            return true;
        case 0x58D7ULL:
            return true;
        case 0xA7ULL:
            return true;
        case 0xABULL:
            return true;
        case 0xA3ULL:
            return false;
        case 0xA0ULL:
            return true;
        case 0xA1ULL:
            return false;
        case 0x9BULL:
            return true;
        case 0xFBULL:
            return true;
        case 0xFAULL:
            return true;
        case 0x75A1ULL:
            return true;
        case 0xA6ULL:
            return true;
        case 0xEEULL:
            return true;
        case 0xA5ULL:
            return false;
        case 0x8EULL:
            return true;
        case 0xE8ULL:
            return true;
        case 0xCCULL:
            return true;
        case 0x1C53BB6BULL:
            return true;
        case 0xBBULL:
            return true;
        case 0xB3ULL:
            return true;
        case 0xB7ULL:
            return true;
        case 0xF7ULL:
            return true;
        case 0xF1ULL:
            return true;
        case 0xF0ULL:
            return true;
        case 0xB2ULL:
            return true;
        case 0x5378ULL:
            return true;
        case 0xEAULL:
            return true;
        case 0xDBULL:
            return true;
        case 0x96ULL:
            return true;
        case 0x97ULL:
            return true;
        case 0x535FULL:
            return true;
        case 0xEBULL:
            return true;
        case 0x1254C367ULL:
            return true;
        case 0x7373ULL:
            return true;
        case 0x63C0ULL:
            return true;
        case 0x68CAULL:
            return true;
        case 0x63CAULL:
            return true;
        case 0x63C5ULL:
            return true;
        case 0x63C9ULL:
            return true;
        case 0x63C4ULL:
            return true;
        case 0x63C6ULL:
            return true;
        case 0x67C8ULL:
            return true;
        case 0x45A3ULL:
            return true;
        case 0x447AULL:
            return true;
        case 0x4484ULL:
            return true;
        case 0x4487ULL:
            return true;
        case 0x4485ULL:
            return false;
        case 0x1043A770ULL:
            return true;
        case 0x45B9ULL:
            return true;
        case 0x45BCULL:
            return true;
        case 0x45BDULL:
            return true;
        case 0x45DBULL:
            return true;
        case 0x45DDULL:
            return true;
        case 0xB6ULL:
            return true;
        case 0x73C4ULL:
            return true;
        case 0x5654ULL:
            return true;
        case 0x91ULL:
            return true;
        case 0x92ULL:
            return true;
        case 0x98ULL:
            return true;
        case 0x4598ULL:
            return true;
        case 0x80ULL:
            return true;
        case 0x85ULL:
            return true;
        case 0x437CULL:
            return true;
        case 0x437EULL:
            return true;
        case 0x1941A469ULL:
            return true;
        case 0x61A7ULL:
            return true;
        case 0x467EULL:
            return true;
        case 0x466EULL:
            return true;
        case 0x4660ULL:
            return true;
        case 0x465CULL:
            return false;
        case 0x46AEULL:
            return true;
        case 0x4675ULL:
            return false;
        case 0x4661ULL:
            return true;
        case 0x4662ULL:
            return true;
        case 0xECULL:
            return false;
        case 0xBFULL:
            return false;
        default:
            return false;
    }
}

std::string reference_codec_family(const std::string& codec) {
    std::string c = lower_ascii(codec);
    if(c == lower_ascii("V_MPEG4/ISO/AVC")) return "video";
    if(c == lower_ascii("V_MPEGH/ISO/HEVC")) return "video";
    if(c == lower_ascii("V_VP8")) return "video";
    if(c == lower_ascii("V_VP9")) return "video";
    if(c == lower_ascii("V_AV1")) return "video";
    if(c == lower_ascii("V_MPEG2")) return "video";
    if(c == lower_ascii("V_THEORA")) return "video";
    if(c == lower_ascii("A_OPUS")) return "audio";
    if(c == lower_ascii("A_VORBIS")) return "audio";
    if(c == lower_ascii("A_AAC")) return "audio";
    if(c == lower_ascii("A_AC3")) return "audio";
    if(c == lower_ascii("A_EAC3")) return "audio";
    if(c == lower_ascii("A_DTS")) return "audio";
    if(c == lower_ascii("A_FLAC")) return "audio";
    if(c == lower_ascii("A_PCM/INT/LIT")) return "audio";
    if(c == lower_ascii("S_TEXT/UTF8")) return "subtitle";
    if(c == lower_ascii("S_TEXT/ASS")) return "subtitle";
    if(c == lower_ascii("S_VOBSUB")) return "subtitle";
    if(c == lower_ascii("S_HDMV/PGS")) return "subtitle";
    if(c == lower_ascii("B_VOBBTN")) return "buttons";
    if(c.rfind("v_",0)==0) return "video";
    if(c.rfind("a_",0)==0) return "audio";
    if(c.rfind("s_",0)==0) return "subtitle";
    return "unknown";
}

std::string reference_codec_media(const std::string& codec) {
    std::string c = lower_ascii(codec);
    if(c == lower_ascii("V_MPEG4/ISO/AVC")) return "mpeg4-iso-avc";
    if(c == lower_ascii("V_MPEGH/ISO/HEVC")) return "mpegh-iso-hevc";
    if(c == lower_ascii("V_VP8")) return "vp8";
    if(c == lower_ascii("V_VP9")) return "vp9";
    if(c == lower_ascii("V_AV1")) return "av1";
    if(c == lower_ascii("V_MPEG2")) return "mpeg2";
    if(c == lower_ascii("V_THEORA")) return "theora";
    if(c == lower_ascii("A_OPUS")) return "opus";
    if(c == lower_ascii("A_VORBIS")) return "vorbis";
    if(c == lower_ascii("A_AAC")) return "aac";
    if(c == lower_ascii("A_AC3")) return "ac3";
    if(c == lower_ascii("A_EAC3")) return "eac3";
    if(c == lower_ascii("A_DTS")) return "dts";
    if(c == lower_ascii("A_FLAC")) return "flac";
    if(c == lower_ascii("A_PCM/INT/LIT")) return "pcm-int-lit";
    if(c == lower_ascii("S_TEXT/UTF8")) return "text-utf8";
    if(c == lower_ascii("S_TEXT/ASS")) return "text-ass";
    if(c == lower_ascii("S_VOBSUB")) return "vobsub";
    if(c == lower_ascii("S_HDMV/PGS")) return "hdmv-pgs";
    if(c == lower_ascii("B_VOBBTN")) return "vobbtn";
    return "generic";
}

std::string reference_payload_role(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return "metadata value";
        case 0x4286ULL:
            return "metadata value";
        case 0x42F7ULL:
            return "metadata value";
        case 0x42F2ULL:
            return "metadata value";
        case 0x42F3ULL:
            return "metadata value";
        case 0x4282ULL:
            return "metadata value";
        case 0x4287ULL:
            return "metadata value";
        case 0x4285ULL:
            return "metadata value";
        case 0x18538067ULL:
            return "container node";
        case 0x114D9B74ULL:
            return "metadata value";
        case 0x4DBBULL:
            return "metadata value";
        case 0x53ABULL:
            return "metadata value";
        case 0x53ACULL:
            return "metadata value";
        case 0x1549A966ULL:
            return "metadata value";
        case 0x2AD7B1ULL:
            return "timing field";
        case 0x4489ULL:
            return "timing field";
        case 0x4D80ULL:
            return "metadata value";
        case 0x5741ULL:
            return "metadata value";
        case 0x73A4ULL:
            return "metadata value";
        case 0x7384ULL:
            return "metadata value";
        case 0x3CB923ULL:
            return "metadata value";
        case 0x3C83ABULL:
            return "metadata value";
        case 0x3EB923ULL:
            return "metadata value";
        case 0x3E83BBULL:
            return "metadata value";
        case 0x1654AE6BULL:
            return "container node";
        case 0xAEULL:
            return "track descriptor";
        case 0xD7ULL:
            return "track descriptor";
        case 0x73C5ULL:
            return "track descriptor";
        case 0x83ULL:
            return "track descriptor";
        case 0xB9ULL:
            return "metadata value";
        case 0x88ULL:
            return "metadata value";
        case 0x55AAULL:
            return "metadata value";
        case 0x9CULL:
            return "metadata value";
        case 0x23E383ULL:
            return "metadata value";
        case 0x23314FULL:
            return "metadata value";
        case 0x536EULL:
            return "metadata value";
        case 0x22B59CULL:
            return "metadata value";
        case 0x86ULL:
            return "track descriptor";
        case 0x63A2ULL:
            return "track descriptor";
        case 0x258688ULL:
            return "metadata value";
        case 0x3A9697ULL:
            return "metadata value";
        case 0x3B4040ULL:
            return "metadata value";
        case 0x26B240ULL:
            return "metadata value";
        case 0xAAULL:
            return "metadata value";
        case 0x6FABULL:
            return "metadata value";
        case 0xE0ULL:
            return "metadata value";
        case 0x9AULL:
            return "metadata value";
        case 0x53B8ULL:
            return "metadata value";
        case 0xB0ULL:
            return "metadata value";
        case 0xBAULL:
            return "metadata value";
        case 0x54AAULL:
            return "metadata value";
        case 0x54BBULL:
            return "metadata value";
        case 0x54CCULL:
            return "metadata value";
        case 0x54DDULL:
            return "metadata value";
        case 0x54B0ULL:
            return "metadata value";
        case 0x54BAULL:
            return "metadata value";
        case 0x54B2ULL:
            return "metadata value";
        case 0x2EB524ULL:
            return "metadata value";
        case 0x55B0ULL:
            return "metadata value";
        case 0x55B1ULL:
            return "metadata value";
        case 0x55B2ULL:
            return "metadata value";
        case 0x55B3ULL:
            return "metadata value";
        case 0x55B4ULL:
            return "metadata value";
        case 0x55B5ULL:
            return "metadata value";
        case 0x55B6ULL:
            return "metadata value";
        case 0x55B7ULL:
            return "metadata value";
        case 0x55B8ULL:
            return "metadata value";
        case 0x55B9ULL:
            return "metadata value";
        case 0x55BAULL:
            return "metadata value";
        case 0x55BBULL:
            return "metadata value";
        case 0x55BCULL:
            return "metadata value";
        case 0x55BDULL:
            return "metadata value";
        case 0xE1ULL:
            return "metadata value";
        case 0xB5ULL:
            return "metadata value";
        case 0x78B5ULL:
            return "metadata value";
        case 0x9FULL:
            return "metadata value";
        case 0x7D7BULL:
            return "metadata value";
        case 0x6264ULL:
            return "metadata value";
        case 0x1F43B675ULL:
            return "container node";
        case 0xE7ULL:
            return "timing field";
        case 0x5854ULL:
            return "metadata value";
        case 0x58D7ULL:
            return "metadata value";
        case 0xA7ULL:
            return "metadata value";
        case 0xABULL:
            return "metadata value";
        case 0xA3ULL:
            return "payload bytes";
        case 0xA0ULL:
            return "metadata value";
        case 0xA1ULL:
            return "payload bytes";
        case 0x9BULL:
            return "metadata value";
        case 0xFBULL:
            return "metadata value";
        case 0xFAULL:
            return "metadata value";
        case 0x75A1ULL:
            return "metadata value";
        case 0xA6ULL:
            return "metadata value";
        case 0xEEULL:
            return "metadata value";
        case 0xA5ULL:
            return "metadata value";
        case 0x8EULL:
            return "metadata value";
        case 0xE8ULL:
            return "metadata value";
        case 0xCCULL:
            return "metadata value";
        case 0x1C53BB6BULL:
            return "container node";
        case 0xBBULL:
            return "metadata value";
        case 0xB3ULL:
            return "timing field";
        case 0xB7ULL:
            return "metadata value";
        case 0xF7ULL:
            return "metadata value";
        case 0xF1ULL:
            return "metadata value";
        case 0xF0ULL:
            return "metadata value";
        case 0xB2ULL:
            return "metadata value";
        case 0x5378ULL:
            return "metadata value";
        case 0xEAULL:
            return "metadata value";
        case 0xDBULL:
            return "metadata value";
        case 0x96ULL:
            return "metadata value";
        case 0x97ULL:
            return "metadata value";
        case 0x535FULL:
            return "metadata value";
        case 0xEBULL:
            return "metadata value";
        case 0x1254C367ULL:
            return "container node";
        case 0x7373ULL:
            return "metadata value";
        case 0x63C0ULL:
            return "metadata value";
        case 0x68CAULL:
            return "metadata value";
        case 0x63CAULL:
            return "metadata value";
        case 0x63C5ULL:
            return "metadata value";
        case 0x63C9ULL:
            return "metadata value";
        case 0x63C4ULL:
            return "metadata value";
        case 0x63C6ULL:
            return "metadata value";
        case 0x67C8ULL:
            return "metadata value";
        case 0x45A3ULL:
            return "metadata value";
        case 0x447AULL:
            return "metadata value";
        case 0x4484ULL:
            return "metadata value";
        case 0x4487ULL:
            return "metadata value";
        case 0x4485ULL:
            return "metadata value";
        case 0x1043A770ULL:
            return "container node";
        case 0x45B9ULL:
            return "metadata value";
        case 0x45BCULL:
            return "metadata value";
        case 0x45BDULL:
            return "metadata value";
        case 0x45DBULL:
            return "metadata value";
        case 0x45DDULL:
            return "metadata value";
        case 0xB6ULL:
            return "metadata value";
        case 0x73C4ULL:
            return "metadata value";
        case 0x5654ULL:
            return "metadata value";
        case 0x91ULL:
            return "timing field";
        case 0x92ULL:
            return "timing field";
        case 0x98ULL:
            return "metadata value";
        case 0x4598ULL:
            return "metadata value";
        case 0x80ULL:
            return "metadata value";
        case 0x85ULL:
            return "metadata value";
        case 0x437CULL:
            return "metadata value";
        case 0x437EULL:
            return "metadata value";
        case 0x1941A469ULL:
            return "container node";
        case 0x61A7ULL:
            return "metadata value";
        case 0x467EULL:
            return "metadata value";
        case 0x466EULL:
            return "metadata value";
        case 0x4660ULL:
            return "metadata value";
        case 0x465CULL:
            return "payload bytes";
        case 0x46AEULL:
            return "metadata value";
        case 0x4675ULL:
            return "metadata value";
        case 0x4661ULL:
            return "metadata value";
        case 0x4662ULL:
            return "metadata value";
        case 0xECULL:
            return "metadata value";
        case 0xBFULL:
            return "metadata value";
        default:
            return "unclassified";
    }
}

std::string reference_cardinality(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return "single";
        case 0x4286ULL:
            return "single";
        case 0x42F7ULL:
            return "single";
        case 0x42F2ULL:
            return "single";
        case 0x42F3ULL:
            return "single";
        case 0x4282ULL:
            return "single";
        case 0x4287ULL:
            return "single";
        case 0x4285ULL:
            return "single";
        case 0x18538067ULL:
            return "single";
        case 0x114D9B74ULL:
            return "single";
        case 0x4DBBULL:
            return "many";
        case 0x53ABULL:
            return "single";
        case 0x53ACULL:
            return "single";
        case 0x1549A966ULL:
            return "single";
        case 0x2AD7B1ULL:
            return "single";
        case 0x4489ULL:
            return "single";
        case 0x4D80ULL:
            return "single";
        case 0x5741ULL:
            return "single";
        case 0x73A4ULL:
            return "single";
        case 0x7384ULL:
            return "single";
        case 0x3CB923ULL:
            return "single";
        case 0x3C83ABULL:
            return "single";
        case 0x3EB923ULL:
            return "single";
        case 0x3E83BBULL:
            return "single";
        case 0x1654AE6BULL:
            return "single";
        case 0xAEULL:
            return "many";
        case 0xD7ULL:
            return "single";
        case 0x73C5ULL:
            return "single";
        case 0x83ULL:
            return "single";
        case 0xB9ULL:
            return "single";
        case 0x88ULL:
            return "single";
        case 0x55AAULL:
            return "single";
        case 0x9CULL:
            return "single";
        case 0x23E383ULL:
            return "single";
        case 0x23314FULL:
            return "single";
        case 0x536EULL:
            return "optional";
        case 0x22B59CULL:
            return "optional";
        case 0x86ULL:
            return "single";
        case 0x63A2ULL:
            return "optional";
        case 0x258688ULL:
            return "optional";
        case 0x3A9697ULL:
            return "single";
        case 0x3B4040ULL:
            return "single";
        case 0x26B240ULL:
            return "single";
        case 0xAAULL:
            return "single";
        case 0x6FABULL:
            return "single";
        case 0xE0ULL:
            return "single";
        case 0x9AULL:
            return "single";
        case 0x53B8ULL:
            return "single";
        case 0xB0ULL:
            return "single";
        case 0xBAULL:
            return "single";
        case 0x54AAULL:
            return "single";
        case 0x54BBULL:
            return "single";
        case 0x54CCULL:
            return "single";
        case 0x54DDULL:
            return "single";
        case 0x54B0ULL:
            return "single";
        case 0x54BAULL:
            return "single";
        case 0x54B2ULL:
            return "single";
        case 0x2EB524ULL:
            return "single";
        case 0x55B0ULL:
            return "single";
        case 0x55B1ULL:
            return "single";
        case 0x55B2ULL:
            return "single";
        case 0x55B3ULL:
            return "single";
        case 0x55B4ULL:
            return "single";
        case 0x55B5ULL:
            return "single";
        case 0x55B6ULL:
            return "single";
        case 0x55B7ULL:
            return "single";
        case 0x55B8ULL:
            return "single";
        case 0x55B9ULL:
            return "single";
        case 0x55BAULL:
            return "single";
        case 0x55BBULL:
            return "single";
        case 0x55BCULL:
            return "single";
        case 0x55BDULL:
            return "single";
        case 0xE1ULL:
            return "single";
        case 0xB5ULL:
            return "single";
        case 0x78B5ULL:
            return "single";
        case 0x9FULL:
            return "single";
        case 0x7D7BULL:
            return "single";
        case 0x6264ULL:
            return "single";
        case 0x1F43B675ULL:
            return "many";
        case 0xE7ULL:
            return "single";
        case 0x5854ULL:
            return "single";
        case 0x58D7ULL:
            return "single";
        case 0xA7ULL:
            return "single";
        case 0xABULL:
            return "single";
        case 0xA3ULL:
            return "many";
        case 0xA0ULL:
            return "single";
        case 0xA1ULL:
            return "single";
        case 0x9BULL:
            return "single";
        case 0xFBULL:
            return "single";
        case 0xFAULL:
            return "single";
        case 0x75A1ULL:
            return "single";
        case 0xA6ULL:
            return "single";
        case 0xEEULL:
            return "single";
        case 0xA5ULL:
            return "single";
        case 0x8EULL:
            return "single";
        case 0xE8ULL:
            return "single";
        case 0xCCULL:
            return "single";
        case 0x1C53BB6BULL:
            return "single";
        case 0xBBULL:
            return "many";
        case 0xB3ULL:
            return "single";
        case 0xB7ULL:
            return "single";
        case 0xF7ULL:
            return "single";
        case 0xF1ULL:
            return "single";
        case 0xF0ULL:
            return "single";
        case 0xB2ULL:
            return "single";
        case 0x5378ULL:
            return "single";
        case 0xEAULL:
            return "single";
        case 0xDBULL:
            return "single";
        case 0x96ULL:
            return "single";
        case 0x97ULL:
            return "single";
        case 0x535FULL:
            return "single";
        case 0xEBULL:
            return "single";
        case 0x1254C367ULL:
            return "single";
        case 0x7373ULL:
            return "many";
        case 0x63C0ULL:
            return "single";
        case 0x68CAULL:
            return "single";
        case 0x63CAULL:
            return "single";
        case 0x63C5ULL:
            return "single";
        case 0x63C9ULL:
            return "single";
        case 0x63C4ULL:
            return "single";
        case 0x63C6ULL:
            return "single";
        case 0x67C8ULL:
            return "many";
        case 0x45A3ULL:
            return "single";
        case 0x447AULL:
            return "single";
        case 0x4484ULL:
            return "single";
        case 0x4487ULL:
            return "single";
        case 0x4485ULL:
            return "single";
        case 0x1043A770ULL:
            return "single";
        case 0x45B9ULL:
            return "single";
        case 0x45BCULL:
            return "single";
        case 0x45BDULL:
            return "single";
        case 0x45DBULL:
            return "single";
        case 0x45DDULL:
            return "single";
        case 0xB6ULL:
            return "many";
        case 0x73C4ULL:
            return "single";
        case 0x5654ULL:
            return "single";
        case 0x91ULL:
            return "single";
        case 0x92ULL:
            return "single";
        case 0x98ULL:
            return "single";
        case 0x4598ULL:
            return "single";
        case 0x80ULL:
            return "single";
        case 0x85ULL:
            return "single";
        case 0x437CULL:
            return "single";
        case 0x437EULL:
            return "single";
        case 0x1941A469ULL:
            return "single";
        case 0x61A7ULL:
            return "many";
        case 0x467EULL:
            return "optional";
        case 0x466EULL:
            return "single";
        case 0x4660ULL:
            return "single";
        case 0x465CULL:
            return "single";
        case 0x46AEULL:
            return "single";
        case 0x4675ULL:
            return "single";
        case 0x4661ULL:
            return "single";
        case 0x4662ULL:
            return "single";
        case 0xECULL:
            return "single";
        case 0xBFULL:
            return "single";
        default:
            return "unknown";
    }
}

std::string reference_validation_hint(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return "structural element";
        case 0x4286ULL:
            return "structural element";
        case 0x42F7ULL:
            return "structural element";
        case 0x42F2ULL:
            return "structural element";
        case 0x42F3ULL:
            return "structural element";
        case 0x4282ULL:
            return "must be printable UTF-8";
        case 0x4287ULL:
            return "structural element";
        case 0x4285ULL:
            return "structural element";
        case 0x18538067ULL:
            return "structural element";
        case 0x114D9B74ULL:
            return "structural element";
        case 0x4DBBULL:
            return "structural element";
        case 0x53ABULL:
            return "structural element";
        case 0x53ACULL:
            return "must be monotonic within its parent";
        case 0x1549A966ULL:
            return "structural element";
        case 0x2AD7B1ULL:
            return "structural element";
        case 0x4489ULL:
            return "structural element";
        case 0x4D80ULL:
            return "structural element";
        case 0x5741ULL:
            return "structural element";
        case 0x73A4ULL:
            return "structural element";
        case 0x7384ULL:
            return "structural element";
        case 0x3CB923ULL:
            return "structural element";
        case 0x3C83ABULL:
            return "structural element";
        case 0x3EB923ULL:
            return "structural element";
        case 0x3E83BBULL:
            return "structural element";
        case 0x1654AE6BULL:
            return "structural element";
        case 0xAEULL:
            return "structural element";
        case 0xD7ULL:
            return "must resolve to a declared track";
        case 0x73C5ULL:
            return "structural element";
        case 0x83ULL:
            return "structural element";
        case 0xB9ULL:
            return "structural element";
        case 0x88ULL:
            return "structural element";
        case 0x55AAULL:
            return "structural element";
        case 0x9CULL:
            return "structural element";
        case 0x23E383ULL:
            return "structural element";
        case 0x23314FULL:
            return "structural element";
        case 0x536EULL:
            return "structural element";
        case 0x22B59CULL:
            return "structural element";
        case 0x86ULL:
            return "must be printable UTF-8";
        case 0x63A2ULL:
            return "must remain within element payload";
        case 0x258688ULL:
            return "structural element";
        case 0x3A9697ULL:
            return "structural element";
        case 0x3B4040ULL:
            return "structural element";
        case 0x26B240ULL:
            return "structural element";
        case 0xAAULL:
            return "structural element";
        case 0x6FABULL:
            return "structural element";
        case 0xE0ULL:
            return "structural element";
        case 0x9AULL:
            return "structural element";
        case 0x53B8ULL:
            return "structural element";
        case 0xB0ULL:
            return "structural element";
        case 0xBAULL:
            return "structural element";
        case 0x54AAULL:
            return "structural element";
        case 0x54BBULL:
            return "structural element";
        case 0x54CCULL:
            return "structural element";
        case 0x54DDULL:
            return "structural element";
        case 0x54B0ULL:
            return "structural element";
        case 0x54BAULL:
            return "structural element";
        case 0x54B2ULL:
            return "structural element";
        case 0x2EB524ULL:
            return "structural element";
        case 0x55B0ULL:
            return "structural element";
        case 0x55B1ULL:
            return "structural element";
        case 0x55B2ULL:
            return "structural element";
        case 0x55B3ULL:
            return "structural element";
        case 0x55B4ULL:
            return "structural element";
        case 0x55B5ULL:
            return "structural element";
        case 0x55B6ULL:
            return "structural element";
        case 0x55B7ULL:
            return "structural element";
        case 0x55B8ULL:
            return "structural element";
        case 0x55B9ULL:
            return "structural element";
        case 0x55BAULL:
            return "structural element";
        case 0x55BBULL:
            return "structural element";
        case 0x55BCULL:
            return "structural element";
        case 0x55BDULL:
            return "structural element";
        case 0xE1ULL:
            return "structural element";
        case 0xB5ULL:
            return "structural element";
        case 0x78B5ULL:
            return "structural element";
        case 0x9FULL:
            return "structural element";
        case 0x7D7BULL:
            return "structural element";
        case 0x6264ULL:
            return "structural element";
        case 0x1F43B675ULL:
            return "structural element";
        case 0xE7ULL:
            return "must be monotonic within its parent";
        case 0x5854ULL:
            return "structural element";
        case 0x58D7ULL:
            return "must resolve to a declared track";
        case 0xA7ULL:
            return "structural element";
        case 0xABULL:
            return "structural element";
        case 0xA3ULL:
            return "must remain within element payload";
        case 0xA0ULL:
            return "structural element";
        case 0xA1ULL:
            return "must remain within element payload";
        case 0x9BULL:
            return "structural element";
        case 0xFBULL:
            return "structural element";
        case 0xFAULL:
            return "structural element";
        case 0x75A1ULL:
            return "structural element";
        case 0xA6ULL:
            return "structural element";
        case 0xEEULL:
            return "structural element";
        case 0xA5ULL:
            return "structural element";
        case 0x8EULL:
            return "structural element";
        case 0xE8ULL:
            return "structural element";
        case 0xCCULL:
            return "structural element";
        case 0x1C53BB6BULL:
            return "structural element";
        case 0xBBULL:
            return "structural element";
        case 0xB3ULL:
            return "must be monotonic within its parent";
        case 0xB7ULL:
            return "structural element";
        case 0xF7ULL:
            return "must resolve to a declared track";
        case 0xF1ULL:
            return "must be monotonic within its parent";
        case 0xF0ULL:
            return "structural element";
        case 0xB2ULL:
            return "structural element";
        case 0x5378ULL:
            return "structural element";
        case 0xEAULL:
            return "structural element";
        case 0xDBULL:
            return "structural element";
        case 0x96ULL:
            return "structural element";
        case 0x97ULL:
            return "structural element";
        case 0x535FULL:
            return "structural element";
        case 0xEBULL:
            return "structural element";
        case 0x1254C367ULL:
            return "structural element";
        case 0x7373ULL:
            return "structural element";
        case 0x63C0ULL:
            return "structural element";
        case 0x68CAULL:
            return "structural element";
        case 0x63CAULL:
            return "structural element";
        case 0x63C5ULL:
            return "structural element";
        case 0x63C9ULL:
            return "structural element";
        case 0x63C4ULL:
            return "structural element";
        case 0x63C6ULL:
            return "structural element";
        case 0x67C8ULL:
            return "structural element";
        case 0x45A3ULL:
            return "must be printable UTF-8";
        case 0x447AULL:
            return "structural element";
        case 0x4484ULL:
            return "structural element";
        case 0x4487ULL:
            return "must be printable UTF-8";
        case 0x4485ULL:
            return "structural element";
        case 0x1043A770ULL:
            return "structural element";
        case 0x45B9ULL:
            return "structural element";
        case 0x45BCULL:
            return "structural element";
        case 0x45BDULL:
            return "structural element";
        case 0x45DBULL:
            return "structural element";
        case 0x45DDULL:
            return "structural element";
        case 0xB6ULL:
            return "structural element";
        case 0x73C4ULL:
            return "structural element";
        case 0x5654ULL:
            return "structural element";
        case 0x91ULL:
            return "must be monotonic within its parent";
        case 0x92ULL:
            return "structural element";
        case 0x98ULL:
            return "structural element";
        case 0x4598ULL:
            return "structural element";
        case 0x80ULL:
            return "structural element";
        case 0x85ULL:
            return "must be printable UTF-8";
        case 0x437CULL:
            return "structural element";
        case 0x437EULL:
            return "structural element";
        case 0x1941A469ULL:
            return "structural element";
        case 0x61A7ULL:
            return "structural element";
        case 0x467EULL:
            return "structural element";
        case 0x466EULL:
            return "must be printable UTF-8";
        case 0x4660ULL:
            return "structural element";
        case 0x465CULL:
            return "must remain within element payload";
        case 0x46AEULL:
            return "structural element";
        case 0x4675ULL:
            return "structural element";
        case 0x4661ULL:
            return "structural element";
        case 0x4662ULL:
            return "structural element";
        case 0xECULL:
            return "structural element";
        case 0xBFULL:
            return "structural element";
        default:
            return "none";
    }
}

std::string reference_report_section(uint64_t id) {
    switch(id) {
        case 0x1A45DFA3ULL:
            return "header";
        case 0x4286ULL:
            return "header";
        case 0x42F7ULL:
            return "header";
        case 0x42F2ULL:
            return "header";
        case 0x42F3ULL:
            return "header";
        case 0x4282ULL:
            return "header";
        case 0x4287ULL:
            return "header";
        case 0x4285ULL:
            return "header";
        case 0x18538067ULL:
            return "header";
        case 0x114D9B74ULL:
            return "header";
        case 0x4DBBULL:
            return "header";
        case 0x53ABULL:
            return "header";
        case 0x53ACULL:
            return "header";
        case 0x1549A966ULL:
            return "header";
        case 0x2AD7B1ULL:
            return "header";
        case 0x4489ULL:
            return "header";
        case 0x4D80ULL:
            return "header";
        case 0x5741ULL:
            return "header";
        case 0x73A4ULL:
            return "header";
        case 0x7384ULL:
            return "header";
        case 0x3CB923ULL:
            return "header";
        case 0x3C83ABULL:
            return "header";
        case 0x3EB923ULL:
            return "header";
        case 0x3E83BBULL:
            return "header";
        case 0x1654AE6BULL:
            return "tracks";
        case 0xAEULL:
            return "tracks";
        case 0xD7ULL:
            return "tracks";
        case 0x73C5ULL:
            return "tracks";
        case 0x83ULL:
            return "tracks";
        case 0xB9ULL:
            return "header";
        case 0x88ULL:
            return "header";
        case 0x55AAULL:
            return "header";
        case 0x9CULL:
            return "header";
        case 0x23E383ULL:
            return "header";
        case 0x23314FULL:
            return "header";
        case 0x536EULL:
            return "header";
        case 0x22B59CULL:
            return "header";
        case 0x86ULL:
            return "tracks";
        case 0x63A2ULL:
            return "tracks";
        case 0x258688ULL:
            return "header";
        case 0x3A9697ULL:
            return "header";
        case 0x3B4040ULL:
            return "header";
        case 0x26B240ULL:
            return "header";
        case 0xAAULL:
            return "header";
        case 0x6FABULL:
            return "header";
        case 0xE0ULL:
            return "tracks";
        case 0x9AULL:
            return "header";
        case 0x53B8ULL:
            return "header";
        case 0xB0ULL:
            return "header";
        case 0xBAULL:
            return "header";
        case 0x54AAULL:
            return "header";
        case 0x54BBULL:
            return "header";
        case 0x54CCULL:
            return "header";
        case 0x54DDULL:
            return "header";
        case 0x54B0ULL:
            return "header";
        case 0x54BAULL:
            return "header";
        case 0x54B2ULL:
            return "header";
        case 0x2EB524ULL:
            return "header";
        case 0x55B0ULL:
            return "header";
        case 0x55B1ULL:
            return "header";
        case 0x55B2ULL:
            return "header";
        case 0x55B3ULL:
            return "header";
        case 0x55B4ULL:
            return "header";
        case 0x55B5ULL:
            return "header";
        case 0x55B6ULL:
            return "header";
        case 0x55B7ULL:
            return "header";
        case 0x55B8ULL:
            return "header";
        case 0x55B9ULL:
            return "header";
        case 0x55BAULL:
            return "header";
        case 0x55BBULL:
            return "header";
        case 0x55BCULL:
            return "header";
        case 0x55BDULL:
            return "header";
        case 0xE1ULL:
            return "tracks";
        case 0xB5ULL:
            return "header";
        case 0x78B5ULL:
            return "header";
        case 0x9FULL:
            return "header";
        case 0x7D7BULL:
            return "header";
        case 0x6264ULL:
            return "header";
        case 0x1F43B675ULL:
            return "clusters";
        case 0xE7ULL:
            return "clusters";
        case 0x5854ULL:
            return "header";
        case 0x58D7ULL:
            return "header";
        case 0xA7ULL:
            return "header";
        case 0xABULL:
            return "header";
        case 0xA3ULL:
            return "clusters";
        case 0xA0ULL:
            return "clusters";
        case 0xA1ULL:
            return "clusters";
        case 0x9BULL:
            return "clusters";
        case 0xFBULL:
            return "clusters";
        case 0xFAULL:
            return "header";
        case 0x75A1ULL:
            return "header";
        case 0xA6ULL:
            return "header";
        case 0xEEULL:
            return "header";
        case 0xA5ULL:
            return "header";
        case 0x8EULL:
            return "header";
        case 0xE8ULL:
            return "header";
        case 0xCCULL:
            return "header";
        case 0x1C53BB6BULL:
            return "cues";
        case 0xBBULL:
            return "cues";
        case 0xB3ULL:
            return "cues";
        case 0xB7ULL:
            return "cues";
        case 0xF7ULL:
            return "cues";
        case 0xF1ULL:
            return "cues";
        case 0xF0ULL:
            return "cues";
        case 0xB2ULL:
            return "header";
        case 0x5378ULL:
            return "header";
        case 0xEAULL:
            return "header";
        case 0xDBULL:
            return "header";
        case 0x96ULL:
            return "header";
        case 0x97ULL:
            return "header";
        case 0x535FULL:
            return "header";
        case 0xEBULL:
            return "header";
        case 0x1254C367ULL:
            return "metadata";
        case 0x7373ULL:
            return "metadata";
        case 0x63C0ULL:
            return "header";
        case 0x68CAULL:
            return "header";
        case 0x63CAULL:
            return "header";
        case 0x63C5ULL:
            return "header";
        case 0x63C9ULL:
            return "header";
        case 0x63C4ULL:
            return "header";
        case 0x63C6ULL:
            return "header";
        case 0x67C8ULL:
            return "metadata";
        case 0x45A3ULL:
            return "metadata";
        case 0x447AULL:
            return "header";
        case 0x4484ULL:
            return "header";
        case 0x4487ULL:
            return "metadata";
        case 0x4485ULL:
            return "header";
        case 0x1043A770ULL:
            return "chapters";
        case 0x45B9ULL:
            return "chapters";
        case 0x45BCULL:
            return "header";
        case 0x45BDULL:
            return "header";
        case 0x45DBULL:
            return "header";
        case 0x45DDULL:
            return "header";
        case 0xB6ULL:
            return "chapters";
        case 0x73C4ULL:
            return "chapters";
        case 0x5654ULL:
            return "header";
        case 0x91ULL:
            return "chapters";
        case 0x92ULL:
            return "header";
        case 0x98ULL:
            return "header";
        case 0x4598ULL:
            return "header";
        case 0x80ULL:
            return "chapters";
        case 0x85ULL:
            return "chapters";
        case 0x437CULL:
            return "header";
        case 0x437EULL:
            return "header";
        case 0x1941A469ULL:
            return "attachments";
        case 0x61A7ULL:
            return "attachments";
        case 0x467EULL:
            return "header";
        case 0x466EULL:
            return "attachments";
        case 0x4660ULL:
            return "header";
        case 0x465CULL:
            return "attachments";
        case 0x46AEULL:
            return "header";
        case 0x4675ULL:
            return "header";
        case 0x4661ULL:
            return "header";
        case 0x4662ULL:
            return "header";
        case 0xECULL:
            return "header";
        case 0xBFULL:
            return "header";
        default:
            return "general";
    }
}

std::string reference_codec_private_shape(const std::string& codec) {
    std::string c = lower_ascii(codec);
    if(c == lower_ascii("V_MPEG4/ISO/AVC"))
        return "avcc record";
    if(c == lower_ascii("V_MPEGH/ISO/HEVC"))
        return "hvcC record";
    if(c == lower_ascii("V_VP8"))
        return "none";
    if(c == lower_ascii("V_VP9"))
        return "none";
    if(c == lower_ascii("V_AV1"))
        return "obu sequence header";
    if(c == lower_ascii("V_MPEG2"))
        return "codec-specific private bytes";
    if(c == lower_ascii("V_THEORA"))
        return "codec-specific private bytes";
    if(c == lower_ascii("V_MJPEG"))
        return "codec-specific private bytes";
    if(c == lower_ascii("V_UNCOMPRESSED"))
        return "codec-specific private bytes";
    if(c == lower_ascii("V_QUICKTIME"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_OPUS"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_VORBIS"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_AAC"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_AC3"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_EAC3"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_DTS"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_FLAC"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_MPEG/L2"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_MPEG/L3"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_PCM/INT/LIT"))
        return "none";
    if(c == lower_ascii("A_PCM/INT/BIG"))
        return "none";
    if(c == lower_ascii("A_PCM/FLOAT/IEEE"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_ALAC"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_TRUEHD"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_MLP"))
        return "codec-specific private bytes";
    if(c == lower_ascii("A_REAL/14_4"))
        return "codec-specific private bytes";
    if(c == lower_ascii("S_TEXT/UTF8"))
        return "codec-specific private bytes";
    if(c == lower_ascii("S_TEXT/ASS"))
        return "codec-specific private bytes";
    if(c == lower_ascii("S_TEXT/SSA"))
        return "codec-specific private bytes";
    if(c == lower_ascii("S_TEXT/WEBVTT"))
        return "codec-specific private bytes";
    if(c == lower_ascii("S_VOBSUB"))
        return "codec-specific private bytes";
    if(c == lower_ascii("S_HDMV/PGS"))
        return "codec-specific private bytes";
    if(c == lower_ascii("S_KATE"))
        return "codec-specific private bytes";
    if(c == lower_ascii("B_VOBBTN"))
        return "codec-specific private bytes";
    return "unspecified";
}

std::string reference_codec_risk_note(const std::string& codec) {
    std::string c = lower_ascii(codec);
    if(c == lower_ascii("V_MPEG4/ISO/AVC"))
        return "parameter-set parser";
    if(c == lower_ascii("V_MPEGH/ISO/HEVC"))
        return "parameter-set parser";
    if(c == lower_ascii("V_VP8"))
        return "generic packet stream";
    if(c == lower_ascii("V_VP9"))
        return "generic packet stream";
    if(c == lower_ascii("V_AV1"))
        return "generic packet stream";
    if(c == lower_ascii("V_MPEG2"))
        return "parameter-set parser";
    if(c == lower_ascii("V_THEORA"))
        return "generic packet stream";
    if(c == lower_ascii("V_MJPEG"))
        return "generic packet stream";
    if(c == lower_ascii("V_UNCOMPRESSED"))
        return "generic packet stream";
    if(c == lower_ascii("V_QUICKTIME"))
        return "generic packet stream";
    if(c == lower_ascii("A_OPUS"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_VORBIS"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_AAC"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_AC3"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_EAC3"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_DTS"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_FLAC"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_MPEG/L2"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_MPEG/L3"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_PCM/INT/LIT"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_PCM/INT/BIG"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_PCM/FLOAT/IEEE"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_ALAC"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_TRUEHD"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_MLP"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("A_REAL/14_4"))
        return "lacing-sensitive audio packets";
    if(c == lower_ascii("S_TEXT/UTF8"))
        return "text normalization";
    if(c == lower_ascii("S_TEXT/ASS"))
        return "text normalization";
    if(c == lower_ascii("S_TEXT/SSA"))
        return "text normalization";
    if(c == lower_ascii("S_TEXT/WEBVTT"))
        return "text normalization";
    if(c == lower_ascii("S_VOBSUB"))
        return "bitmap packet dimensions";
    if(c == lower_ascii("S_HDMV/PGS"))
        return "bitmap packet dimensions";
    if(c == lower_ascii("S_KATE"))
        return "bitmap packet dimensions";
    if(c == lower_ascii("B_VOBBTN"))
        return "generic packet stream";
    return "generic packet stream";
}

unsigned reference_codec_default_priority(const std::string& codec) {
    std::string c = lower_ascii(codec);
    if(c == lower_ascii("V_MPEG4/ISO/AVC"))
        return 100;
    if(c == lower_ascii("V_MPEGH/ISO/HEVC"))
        return 99;
    if(c == lower_ascii("V_VP8"))
        return 98;
    if(c == lower_ascii("V_VP9"))
        return 97;
    if(c == lower_ascii("V_AV1"))
        return 96;
    if(c == lower_ascii("V_MPEG2"))
        return 95;
    if(c == lower_ascii("V_THEORA"))
        return 94;
    if(c == lower_ascii("V_MJPEG"))
        return 93;
    if(c == lower_ascii("V_UNCOMPRESSED"))
        return 92;
    if(c == lower_ascii("V_QUICKTIME"))
        return 91;
    if(c == lower_ascii("A_OPUS"))
        return 60;
    if(c == lower_ascii("A_VORBIS"))
        return 59;
    if(c == lower_ascii("A_AAC"))
        return 58;
    if(c == lower_ascii("A_AC3"))
        return 57;
    if(c == lower_ascii("A_EAC3"))
        return 56;
    if(c == lower_ascii("A_DTS"))
        return 55;
    if(c == lower_ascii("A_FLAC"))
        return 54;
    if(c == lower_ascii("A_MPEG/L2"))
        return 53;
    if(c == lower_ascii("A_MPEG/L3"))
        return 52;
    if(c == lower_ascii("A_PCM/INT/LIT"))
        return 51;
    if(c == lower_ascii("A_PCM/INT/BIG"))
        return 50;
    if(c == lower_ascii("A_PCM/FLOAT/IEEE"))
        return 49;
    if(c == lower_ascii("A_ALAC"))
        return 48;
    if(c == lower_ascii("A_TRUEHD"))
        return 47;
    if(c == lower_ascii("A_MLP"))
        return 46;
    if(c == lower_ascii("A_REAL/14_4"))
        return 45;
    if(c == lower_ascii("S_TEXT/UTF8"))
        return 14;
    if(c == lower_ascii("S_TEXT/ASS"))
        return 13;
    if(c == lower_ascii("S_TEXT/SSA"))
        return 12;
    if(c == lower_ascii("S_TEXT/WEBVTT"))
        return 11;
    if(c == lower_ascii("S_VOBSUB"))
        return 10;
    if(c == lower_ascii("S_HDMV/PGS"))
        return 9;
    if(c == lower_ascii("S_KATE"))
        return 8;
    if(c == lower_ascii("B_VOBBTN"))
        return 7;
    return 1;
}

std::string reference_language_family(const std::string& language) {
    std::string l = lower_ascii(language);
    if(l == "eng")
        return "germanic";
    if(l == "deu")
        return "germanic";
    if(l == "fra")
        return "romance";
    if(l == "spa")
        return "romance";
    if(l == "ita")
        return "romance";
    if(l == "por")
        return "romance";
    if(l == "rus")
        return "slavic";
    if(l == "jpn")
        return "east-asian";
    if(l == "kor")
        return "east-asian";
    if(l == "zho")
        return "east-asian";
    if(l == "ara")
        return "semitic";
    if(l == "hin")
        return "indo-iranian";
    if(l == "ben")
        return "indo-iranian";
    if(l == "urd")
        return "indo-iranian";
    if(l == "tur")
        return "other";
    if(l == "nld")
        return "germanic";
    if(l == "swe")
        return "germanic";
    if(l == "nor")
        return "germanic";
    if(l == "dan")
        return "germanic";
    if(l == "fin")
        return "other";
    if(l == "pol")
        return "slavic";
    if(l == "ces")
        return "slavic";
    if(l == "slk")
        return "slavic";
    if(l == "hun")
        return "other";
    if(l == "ell")
        return "other";
    if(l == "heb")
        return "semitic";
    if(l == "tha")
        return "other";
    if(l == "vie")
        return "other";
    if(l == "ind")
        return "other";
    if(l == "msa")
        return "other";
    if(l == "ron")
        return "romance";
    if(l == "bul")
        return "slavic";
    if(l == "ukr")
        return "slavic";
    if(l == "hrv")
        return "slavic";
    if(l == "srp")
        return "slavic";
    if(l == "slv")
        return "slavic";
    if(l == "est")
        return "other";
    if(l == "lav")
        return "other";
    if(l == "lit")
        return "other";
    if(l == "cat")
        return "romance";
    if(l == "eus")
        return "other";
    if(l == "glg")
        return "romance";
    if(l == "isl")
        return "germanic";
    if(l == "gle")
        return "other";
    if(l == "cym")
        return "other";
    if(l == "afr")
        return "germanic";
    if(l == "swa")
        return "other";
    if(l == "tam")
        return "other";
    if(l == "tel")
        return "other";
    if(l == "kan")
        return "other";
    if(l == "mal")
        return "other";
    if(l == "mar")
        return "indo-iranian";
    if(l == "guj")
        return "indo-iranian";
    if(l == "pan")
        return "indo-iranian";
    if(l == "nep")
        return "indo-iranian";
    if(l == "fas")
        return "indo-iranian";
    if(l == "kur")
        return "indo-iranian";
    if(l == "aze")
        return "other";
    if(l == "kat")
        return "other";
    if(l == "hye")
        return "other";
    if(l == "kaz")
        return "other";
    if(l == "uzb")
        return "other";
    if(l == "mon")
        return "east-asian";
    return "unknown";
}

std::string reference_language_display(const std::string& language) {
    std::string l = lower_ascii(language);
    if(l == "eng")
        return "ENG";
    if(l == "deu")
        return "DEU";
    if(l == "fra")
        return "FRA";
    if(l == "spa")
        return "SPA";
    if(l == "ita")
        return "ITA";
    if(l == "por")
        return "POR";
    if(l == "rus")
        return "RUS";
    if(l == "jpn")
        return "JPN";
    if(l == "kor")
        return "KOR";
    if(l == "zho")
        return "ZHO";
    if(l == "ara")
        return "ARA";
    if(l == "hin")
        return "HIN";
    if(l == "ben")
        return "BEN";
    if(l == "urd")
        return "URD";
    if(l == "tur")
        return "TUR";
    if(l == "nld")
        return "NLD";
    if(l == "swe")
        return "SWE";
    if(l == "nor")
        return "NOR";
    if(l == "dan")
        return "DAN";
    if(l == "fin")
        return "FIN";
    if(l == "pol")
        return "POL";
    if(l == "ces")
        return "CES";
    if(l == "slk")
        return "SLK";
    if(l == "hun")
        return "HUN";
    if(l == "ell")
        return "ELL";
    if(l == "heb")
        return "HEB";
    if(l == "tha")
        return "THA";
    if(l == "vie")
        return "VIE";
    if(l == "ind")
        return "IND";
    if(l == "msa")
        return "MSA";
    if(l == "ron")
        return "RON";
    if(l == "bul")
        return "BUL";
    if(l == "ukr")
        return "UKR";
    if(l == "hrv")
        return "HRV";
    if(l == "srp")
        return "SRP";
    if(l == "slv")
        return "SLV";
    if(l == "est")
        return "EST";
    if(l == "lav")
        return "LAV";
    if(l == "lit")
        return "LIT";
    if(l == "cat")
        return "CAT";
    if(l == "eus")
        return "EUS";
    if(l == "glg")
        return "GLG";
    if(l == "isl")
        return "ISL";
    if(l == "gle")
        return "GLE";
    if(l == "cym")
        return "CYM";
    if(l == "afr")
        return "AFR";
    if(l == "swa")
        return "SWA";
    if(l == "tam")
        return "TAM";
    if(l == "tel")
        return "TEL";
    if(l == "kan")
        return "KAN";
    if(l == "mal")
        return "MAL";
    if(l == "mar")
        return "MAR";
    if(l == "guj")
        return "GUJ";
    if(l == "pan")
        return "PAN";
    if(l == "nep")
        return "NEP";
    if(l == "fas")
        return "FAS";
    if(l == "kur")
        return "KUR";
    if(l == "aze")
        return "AZE";
    if(l == "kat")
        return "KAT";
    if(l == "hye")
        return "HYE";
    if(l == "kaz")
        return "KAZ";
    if(l == "uzb")
        return "UZB";
    if(l == "mon")
        return "MON";
    return language;
}

std::string reference_mime_family(const std::string& mime) {
    std::string m = lower_ascii(mime);
    if(m == "image/jpeg")
        return "image";
    if(m == "image/png")
        return "image";
    if(m == "image/webp")
        return "image";
    if(m == "image/gif")
        return "image";
    if(m == "image/svg+xml")
        return "image";
    if(m == "application/x-truetype-font")
        return "font";
    if(m == "font/ttf")
        return "font";
    if(m == "font/otf")
        return "font";
    if(m == "application/font-woff")
        return "font";
    if(m == "application/font-woff2")
        return "font";
    if(m == "text/plain")
        return "text";
    if(m == "text/srt")
        return "text";
    if(m == "text/vtt")
        return "text";
    if(m == "application/x-subrip")
        return "text";
    if(m == "application/pgp-signature")
        return "binary";
    if(m == "application/octet-stream")
        return "binary";
    if(m == "application/xml")
        return "document";
    if(m == "application/json")
        return "document";
    if(m == "audio/ogg")
        return "media";
    if(m == "video/webm")
        return "media";
    if(m == "application/x-matroska")
        return "binary";
    if(m == "application/pdf")
        return "document";
    if(m == "image/bmp")
        return "image";
    if(m == "image/tiff")
        return "image";
    if(m == "application/zip")
        return "archive";
    if(m == "application/gzip")
        return "archive";
    if(m == "application/x-7z-compressed")
        return "archive";
    if(m == "application/x-bzip2")
        return "archive";
    if(m.rfind("image/",0)==0) return "image";
    if(m.rfind("text/",0)==0) return "text";
    if(m.rfind("audio/",0)==0 || m.rfind("video/",0)==0) return "media";
    return "binary";
}

std::string reference_extension_family(const std::string& ext) {
    std::string e = lower_ascii(ext);
    if(e == "jpg")
        return "image";
    if(e == "jpeg")
        return "image";
    if(e == "png")
        return "image";
    if(e == "webp")
        return "image";
    if(e == "gif")
        return "image";
    if(e == "svg")
        return "image";
    if(e == "ttf")
        return "font";
    if(e == "otf")
        return "font";
    if(e == "woff")
        return "font";
    if(e == "woff2")
        return "font";
    if(e == "srt")
        return "subtitle";
    if(e == "ass")
        return "subtitle";
    if(e == "ssa")
        return "subtitle";
    if(e == "vtt")
        return "subtitle";
    if(e == "txt")
        return "document";
    if(e == "xml")
        return "document";
    if(e == "json")
        return "document";
    if(e == "pdf")
        return "document";
    if(e == "zip")
        return "archive";
    if(e == "gz")
        return "archive";
    if(e == "bz2")
        return "archive";
    if(e == "7z")
        return "archive";
    if(e == "bmp")
        return "image";
    if(e == "tif")
        return "image";
    if(e == "tiff")
        return "image";
    if(e == "webm")
        return "media";
    if(e == "mkv")
        return "media";
    if(e == "mka")
        return "media";
    if(e == "mks")
        return "media";
    if(e == "opus")
        return "media";
    if(e == "ogg")
        return "media";
    if(e == "flac")
        return "media";
    if(e == "aac")
        return "media";
    if(e == "ac3")
        return "media";
    if(e == "eac3")
        return "media";
    if(e == "dts")
        return "media";
    return "unknown";
}

void attach_extension_reference(Movie& movie) {
    std::map<std::string, unsigned> families;
    for(auto& attachment : movie.segment.attachments) {
        std::string ext;
        auto pos = attachment.name.find_last_of('.');
        if(pos != std::string::npos) ext = attachment.name.substr(pos + 1);
        families[reference_extension_family(ext)]++;
    }
    for(auto& kv : families) {
        movie.segment.tag_index["attachment.extension_family." + kv.first] = std::to_string(kv.second);
    }
}

void attach_mime_reference(Movie& movie) {
    std::map<std::string, unsigned> families;
    for(auto& attachment : movie.segment.attachments) {
        std::string family = reference_mime_family(attachment.probe);
        families[family]++;
        if(family == "archive") movie.segment.warnings.push_back("attachment-reference:archive:" + attachment.name);
    }
    for(auto& kv : families) movie.segment.tag_index["attachment.mime_family." + kv.first] = std::to_string(kv.second);
}

void attach_language_reference(Movie& movie) {
    std::map<std::string, unsigned> families;
    for(auto& tag : movie.segment.tags) {
        std::string key = lower_ascii(tag.name);
        if(key.find("language") != std::string::npos) {
            families[reference_language_family(tag.value)]++;
        }
    }
    for(auto& kv : families) {
        movie.segment.tag_index["language.family." + kv.first] = std::to_string(kv.second);
    }
    if(families.empty()) {
        movie.segment.tag_index["language.family.unknown"] = "0";
    }
}

void attach_codec_reference_detail(Movie& movie) {
    for(auto& track : movie.segment.tracks) {
        for(auto& entry : track.entries) {
            std::string prefix = "codec.ref." + std::to_string(track.number) + ".";
            movie.segment.tag_index[prefix + "shape"] = reference_codec_private_shape(entry.codec_id);
            movie.segment.tag_index[prefix + "risk"] = reference_codec_risk_note(entry.codec_id);
            movie.segment.tag_index[prefix + "priority"] = std::to_string(reference_codec_default_priority(entry.codec_id));
            if(reference_codec_private_shape(entry.codec_id) != "none" && entry.private_data.data.empty())
                movie.segment.warnings.push_back("codec-reference:private-missing:" + std::to_string(track.number));
        }
    }
}

void attach_reference_detail(Movie& movie) {
    std::map<std::string, unsigned> sections;
    for(auto& track : movie.segment.tracks) {
        for(auto& entry : track.entries) {
            std::string media = reference_codec_media(entry.codec_id);
            sections[reference_codec_family(entry.codec_id)]++;
            if(media == "generic") movie.segment.warnings.push_back("reference:generic-codec:" + std::to_string(track.number));
        }
    }
    for(auto& kv : sections) movie.segment.tag_index["reference.section." + kv.first] = std::to_string(kv.second);
    movie.segment.tag_index["reference.segment.role"] = reference_payload_role(0x18538067ULL);
    movie.segment.tag_index["reference.track.cardinality"] = reference_cardinality(0xAEULL);
    movie.segment.tag_index["reference.block.hint"] = reference_validation_hint(0xA3ULL);
    movie.segment.tag_index["reference.cue.section"] = reference_report_section(0x1C53BB6BULL);
    attach_codec_reference_detail(movie);
    attach_language_reference(movie);
    attach_mime_reference(movie);
    attach_extension_reference(movie);
}

void attach_reference_summary(Movie& movie) {
    unsigned video=0, audio=0, subtitle=0, other=0;
    for(auto& track : movie.segment.tracks) {
        for(auto& entry : track.entries) {
            std::string fam = reference_codec_family(entry.codec_id);
            if(fam == "video") ++video;
            else if(fam == "audio") ++audio;
            else if(fam == "subtitle") ++subtitle;
            else ++other;
            movie.segment.tag_index["reference.codec." + std::to_string(track.number)] = reference_codec_media(entry.codec_id);
        }
    }
    movie.segment.tag_index["reference.video_tracks"] = std::to_string(video);
    movie.segment.tag_index["reference.audio_tracks"] = std::to_string(audio);
    movie.segment.tag_index["reference.subtitle_tracks"] = std::to_string(subtitle);
    movie.segment.tag_index["reference.other_tracks"] = std::to_string(other);
    if(video == 0 && audio == 0 && subtitle == 0) movie.segment.warnings.push_back("reference:no-media-codecs");
    attach_reference_detail(movie);
}
}
