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

void classify_codec_private(SampleEntry& e){
 std::string id=lower_ascii(e.codec_id);
 if(id.find("avc")!=std::string::npos) e.private_data.family="avc";
 else if(id.find("hevc")!=std::string::npos||id.find("h265")!=std::string::npos) e.private_data.family="hevc";
 else if(id.find("vp9")!=std::string::npos) e.private_data.family="vp9";
 else if(id.find("opus")!=std::string::npos) e.private_data.family="opus";
 else e.private_data.family="generic";
 }

void analyze_codec_private(SampleEntry& e, Diagnostics& diag){
 if(e.private_data.family=="avc") parse_avc_private(e,diag);
 else if(e.private_data.family=="opus") parse_opus_private(e,diag);
 else if(e.private_data.family=="vp9") parse_vp9_private(e,diag);
 }

}
