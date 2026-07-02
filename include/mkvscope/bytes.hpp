
#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <limits>
namespace mkv {

class Diagnostics;

class ByteView {

    const uint8_t* data_{
};
 size_t size_{
};

public:
    ByteView() = default;

    ByteView(const uint8_t* d, size_t s) : data_(d), size_(s) {
}
    const uint8_t* data() const {
 return data_;
 }

    size_t size() const {
 return size_;
 }

    bool empty() const {
 return size_ == 0;
 }

    bool has(size_t off, size_t len) const {
 return off <= size_ && len <= size_ - off;
 }

    uint8_t u8(size_t off, uint8_t def=0) const {
 return off < size_ ? data_[off] : def;
 }

    uint16_t be16(size_t off, uint16_t def=0) const;

    uint32_t be32(size_t off, uint32_t def=0) const;

    uint64_t be64(size_t off, uint64_t def=0) const;

    ByteView sub(size_t off, size_t len) const;

    std::vector<uint8_t> vec(size_t off, size_t len) const;

    std::string text(size_t off, size_t len) const;

    void copy_unchecked(size_t off, void* dst, size_t len) const {
 std::memcpy(dst, data_ + off, len);
 }

};

uint64_t saturating_add(uint64_t a, uint64_t b);

uint64_t fnv1a(ByteView v);

}
