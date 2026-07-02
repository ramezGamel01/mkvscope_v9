# mkvscope v9

mkvscope is a first-party C++17 Matroska/WebM EBML inspection library and command-line tool. It parses raw EBML bytes into a typed element tree, builds a Matroska segment model, decodes tracks, clusters, cues, seeks, tags, chapters and attachments, then runs resolver, normalizer, indexing, profile validation and state-machine passes before producing text, JSON and table reports.

Version 9 is focused on hard public-path fuzzing. The important change from v8 is that the product now includes five connected state machines that run after the normal semantic passes: track lifecycle, cluster ordering, cue/seek lattice, tag/attachment binding and codec profile contract. These machines consume the resolved model rather than raw bytes, so a crash candidate must travel through at least eight layers of product behavior before it reaches the target invariant.

Public path layers:
1. byte reader and EBML variable integer decoder
2. EBML element scanner and size-bound tree construction
3. Matroska schema classification
4. Segment builder for Info, Tracks, Clusters, Cues, SeekHead, Tags, Chapters and Attachments
5. track, block, lacing, cue, seek, tag, chapter, attachment and codec-private decoders
6. timeline materialization, cue/cluster resolution and seek lattice reconciliation
7. normalizer, index builders, attachment manifest and chapter binding graph
8. five product state machines over the resolved model
9. WebM/Matroska profile contract checks and report generation

The repository has eight libFuzzer entrypoints: archive, track, cluster, metadata, report, cue lattice, state machine and WebM profile fuzzers. Each fuzzer enters through the public inspection API rather than calling a local helper. The project intentionally avoids generated padding, numbered analyzer modules, bug registries and artificial arithmetic folds.

Build locally:

```sh
cmake -S . -B build -G "Unix Makefiles"
cmake --build build -- -j2
ctest --test-dir build --output-on-failure
```

ClusterFuzzLite builds through `.clusterfuzzlite/build.sh` and does not require Ninja.
