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

static CueTrackPosition read_pos(const Element& e){
 CueTrackPosition p;
 for(const auto& c:e.children){
 if(c.id==id::CueTrack) p.track=(uint32_t)read_uint(c.view());
 else if(c.id==id::CueClusterPosition) p.cluster_position=read_uint(c.view());
 else if(c.id==id::CueRelativePosition) p.relative_position=read_uint(c.view());
 }
 return p;
 }

void decode_cues(const Element& cues, Movie& movie){
 for(auto* cp:children_named(cues,id::CuePoint)){
 CuePoint point;
 if(auto t=first_child(*cp,id::CueTime)) point.time=read_uint(t->view());
 for(auto* pos:children_named(*cp,id::CueTrackPositions)) point.positions.push_back(read_pos(*pos));
 movie.segment.cues.push_back(std::move(point));
 }
 }

}
