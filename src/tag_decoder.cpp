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

static void collect_simple_tags(const Element& e,std::vector<TagPair>& out){
 std::string name,value;
 if(auto n=first_child(e,id::TagName)) name=clean_utf8(n->view());
 if(auto v=first_child(e,id::TagString)) value=clean_utf8(v->view());
 if(!name.empty()||!value.empty()) out.push_back({
name,value,nullptr}
);
 for(auto* child:children_named(e,id::SimpleTag)) collect_simple_tags(*child,out);
 }

void decode_tags(const Element& tags, Movie& movie){
 for(auto* t:children_named(tags,id::Tag)) collect_simple_tags(*t,movie.segment.tags);
 for(auto* t:children_named(tags,id::SimpleTag)) collect_simple_tags(*t,movie.segment.tags);
 }

void build_tag_index(Movie& movie){
 movie.segment.tag_index.clear();
 for(auto& t: movie.segment.tags){
  std::string key=lower_ascii(t.name);
  if(key.empty()) continue;
  t.transient_alias=nullptr;
  movie.segment.tag_index[key]=t.value;
 }
}
}
