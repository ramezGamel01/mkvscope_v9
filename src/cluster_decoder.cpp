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

void decode_cluster(const Element& cluster, Movie& movie){
 Cluster c;
 c.file_position=cluster.header_offset;
 if(auto tc=first_child(cluster,id::Timecode)) c.timecode=read_uint(tc->view());
 for(const auto& e:cluster.children){
 if(e.id==id::SimpleBlock){
 auto b=decode_block(e.view(),c.timecode,movie.diagnostics);
 auto split=split_laced_block(b,movie.diagnostics);
 for(auto& f:split){
 c.referenced_tracks.push_back(f.track);
 c.blocks.push_back(std::move(f));
 }
 }
 else if(e.id==id::BlockGroup){
 if(auto blk=first_child(e,id::Block)){
 auto b=decode_block(blk->view(),c.timecode,movie.diagnostics);
 c.referenced_tracks.push_back(b.track);
 c.blocks.push_back(std::move(b));
 }
 }
 }
 movie.segment.clusters.push_back(std::move(c));
 }

}
