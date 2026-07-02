
#pragma once
#include "mkvscope/bytes.hpp"
#include <string>
#include <vector>
namespace mkv {

struct Element {

    uint64_t id{
};
 uint64_t size{
};
 size_t header_offset{
};
 size_t payload_offset{
};

    unsigned depth{
};
 std::string path;
 std::vector<uint8_t> payload;
 std::vector<Element> children;

    ByteView view() const {
 return ByteView(payload.data(), payload.size());
 }

    bool is(uint64_t x) const {
 return id == x;
 }

};

struct Document {
 std::vector<Element> roots;
 Diagnostics* diagnostics{
};
 }
;
std::string element_path(const Element& e);

const Element* first_child(const Element& e, uint64_t id);

std::vector<const Element*> children_named(const Element& e, uint64_t id);

}
