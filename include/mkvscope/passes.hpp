#pragma once
#include "mkvscope/model.hpp"
#include "mkvscope/state_machines.hpp"
namespace mkv {

void run_deep_validation(Movie& movie);

void validate_ebml_constraints(Movie& movie);

void classify_matroska_profile(Movie& movie);

void reconcile_track_consistency(Movie& movie);

void build_cluster_windows(Movie& movie);

void inspect_block_semantics(Movie& movie);

void reconcile_cue_seek_consistency(Movie& movie);

void normalize_chapter_semantics(Movie& movie);

void index_tag_semantics(Movie& movie);

void catalog_attachments(Movie& movie);

void catalog_codecs(Movie& movie);

void model_timeline_density(Movie& movie);

void derive_report_sections(Movie& movie);

void validate_audio_layouts(Movie& movie);

void validate_video_layouts(Movie& movie);

void classify_subtitle_tracks(Movie& movie);

void derive_seek_spans(Movie& movie);

void reconcile_cluster_tracks(Movie& movie);

void derive_muxing_profile(Movie& movie);

void model_track_cluster_interleave(Movie& movie);

void reconcile_cue_seek_lattice(Movie& movie);

void project_attachment_manifest(Movie& movie);

void derive_codec_transition_graph(Movie& movie);

void synthesize_chapter_toc(Movie& movie);

void enforce_webm_profile_contract(Movie& movie);

void model_seek_shadow_ranges(Movie& movie);

void reconcile_attachment_tag_profile(Movie& movie);

void fold_laced_timeline_spans(Movie& movie);

void project_cue_seek_cluster_witness(Movie& movie);

void derive_codec_profile_contract_v8(Movie& movie);

void bind_chapter_tag_attachment_graph(Movie& movie);

// Runs five product state machines over the resolved Matroska model.
// The machines are deliberately high-level and are invoked only after
// parsing, decoding, resolving, normalizing, indexing and semantic passes.
// This makes fuzzers exercise a full product path rather than a local helper.
void run_product_state_machines(Movie& movie);

}
