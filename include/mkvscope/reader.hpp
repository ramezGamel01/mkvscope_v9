
#pragma once
#include "mkvscope/element.hpp"
#include "mkvscope/diagnostics.hpp"
namespace mkv {

struct ReaderOptions {
 unsigned max_depth{
12}
; unsigned max_children{
12000}
; bool retain_payloads{
true}
; }
;
Document parse_ebml(ByteView bytes, Diagnostics& diag, ReaderOptions opts = {
});

void scan_children(ByteView bytes, size_t start, size_t end, unsigned depth, const std::string& path, std::vector<Element>& out, Diagnostics& diag, const ReaderOptions& opts);

}
