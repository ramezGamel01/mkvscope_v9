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

static Chapter read_chapter(const Element& e){
 Chapter ch;
 for(const auto& c:e.children){
 if(c.id==id::ChapterUID) ch.uid=read_uint(c.view());
 else if(c.id==id::ChapterTimeStart) ch.start=read_uint(c.view());
 else if(c.id==id::ChapterDisplay){
 ChapterDisplay d;
 if(auto s=first_child(c,id::ChapString)) d.text=clean_utf8(s->view());
 ch.display_refs.push_back((uint32_t)read_uint(c.view()));
 ch.displays.push_back(std::move(d));
 }
 else if(c.id==id::ChapterAtom) ch.children.push_back(read_chapter(c));
 }
 return ch;
 }

void decode_chapters(const Element& chapters, Movie& movie){
 for(auto* ed:children_named(chapters,id::EditionEntry)) for(auto* ca:children_named(*ed,id::ChapterAtom)) movie.segment.chapters.push_back(read_chapter(*ca));
 }

static void resolve_one(Chapter& ch,std::vector<std::string>& names){
 for(uint32_t ref: ch.display_refs){
 if(ref < ch.displays.size()) names.push_back(ch.displays[ref].text);
else if(!ch.displays.empty()) names.push_back(ch.displays.front().text);
 }
 for(auto& c:ch.children) resolve_one(c,names);
 }

void resolve_chapter_displays(Movie& movie){
 std::vector<std::string> names;
 for(auto& ch:movie.segment.chapters) resolve_one(ch,names);
 if(!names.empty()) movie.segment.warnings.push_back("chapter-display:"+names.front());
 }

}
