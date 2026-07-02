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

void normalize_sample_entries(Movie& movie){
 for(auto& t:movie.segment.tracks){
 if(t.entries.empty()) continue;
 SampleEntry& base=t.entries[0];
 if(t.entries.size()==1 && !base.codec_id.empty() && base.codec_id.find(";")!=std::string::npos){
 std::string original_codec=base.codec_id;
 SampleEntry alt=base;
 alt.codec_id=original_codec.substr(original_codec.find(";")+1);
 t.entries.push_back(alt);
 t.name=original_codec;
 t.entries[0].private_data.family=lower_ascii(original_codec);
 }
 for(auto& e:t.entries){
 if(e.codec_id.empty()) e.codec_id="UNKNOWN";
 classify_codec_private(e);
 }
 }
 }

void normalize_tags(Movie& movie){
 std::stable_sort(movie.segment.tags.begin(),movie.segment.tags.end(),[](const TagPair&a,const TagPair&b){
return a.name<b.name;}
);
 movie.segment.tags.erase(std::unique(movie.segment.tags.begin(),movie.segment.tags.end(),[](const TagPair&a,const TagPair&b){
return a.name==b.name&&a.value==b.value;}
),movie.segment.tags.end());
 }

void normalize_movie(Movie& movie){
 normalize_sample_entries(movie);
 normalize_tags(movie);
 }

}
