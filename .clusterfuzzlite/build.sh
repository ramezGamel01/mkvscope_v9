#!/bin/bash
set -euo pipefail
cd "$SRC"
CXX_BIN="${CXX:-clang++}"
OUT_DIR="${OUT:-$SRC/out}"
OBJ_DIR="$SRC/build_fuzz_objects"
mkdir -p "$OUT_DIR" "$OBJ_DIR"
CXXFLAGS_IN="${CXXFLAGS:- -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer }"
LIB_FUZZING_ENGINE_IN="${LIB_FUZZING_ENGINE:- -fsanitize=fuzzer }"
mapfile -t SOURCES < <(find src -name '*.cpp' ! -name 'cli_main.cpp' | sort)
compile_one() {
  src="$1"
  base=$(basename "$src" .cpp)
  "$CXX_BIN" $CXXFLAGS_IN -std=c++17 -Iinclude -c "$src" -o "$OBJ_DIR/${base}.o"
}
export CXX_BIN CXXFLAGS_IN OBJ_DIR
export -f compile_one
printf '%s\n' "${SOURCES[@]}" | xargs -n 1 -P "${JOBS:-4}" bash -c 'compile_one "$0"'
OBJECTS=()
for src in "${SOURCES[@]}"; do
  base=$(basename "$src" .cpp)
  OBJECTS+=("$OBJ_DIR/${base}.o")
done
for f in fuzz/*_fuzzer.cc; do
  name=$(basename "$f" .cc)
  "$CXX_BIN" $CXXFLAGS_IN -std=c++17 -Iinclude "${OBJECTS[@]}" "$f" $LIB_FUZZING_ENGINE_IN -o "$OUT_DIR/$name"
done
