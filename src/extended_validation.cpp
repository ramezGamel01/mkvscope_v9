#include "mkvscope/passes.hpp"
#include "mkvscope/reference.hpp"
#include "mkvscope/text.hpp"
#include "mkvscope/ids.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <unordered_map>
namespace mkv {

void run_deep_validation(Movie& movie){

    validate_ebml_constraints(movie);

    classify_matroska_profile(movie);

    reconcile_track_consistency(movie);

    build_cluster_windows(movie);

    inspect_block_semantics(movie);

    reconcile_cue_seek_consistency(movie);

    normalize_chapter_semantics(movie);

    index_tag_semantics(movie);

    catalog_attachments(movie);

    catalog_codecs(movie);

    model_timeline_density(movie);

    derive_report_sections(movie);

    validate_audio_layouts(movie);

    validate_video_layouts(movie);

    classify_subtitle_tracks(movie);

    derive_seek_spans(movie);

    reconcile_cluster_tracks(movie);

    derive_muxing_profile(movie);

    model_track_cluster_interleave(movie);

    reconcile_cue_seek_lattice(movie);

    project_attachment_manifest(movie);

    derive_codec_transition_graph(movie);

    synthesize_chapter_toc(movie);

    enforce_webm_profile_contract(movie);

    model_seek_shadow_ranges(movie);

    reconcile_attachment_tag_profile(movie);

    fold_laced_timeline_spans(movie);

    project_cue_seek_cluster_witness(movie);

    derive_codec_profile_contract_v8(movie);

    bind_chapter_tag_attachment_graph(movie);

    run_product_state_machines(movie);

    attach_reference_summary(movie);

}

}
