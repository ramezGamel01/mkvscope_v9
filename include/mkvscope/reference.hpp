#pragma once
#include <cstdint>
#include <string>
#include "mkvscope/model.hpp"
namespace mkv {
std::string reference_element_name(uint64_t id);
std::string reference_element_type(uint64_t id);
std::string reference_parent_name(uint64_t id);
unsigned reference_element_level(uint64_t id);
bool reference_element_is_seekable(uint64_t id);
std::string reference_codec_family(const std::string& codec);
std::string reference_codec_media(const std::string& codec);
std::string reference_payload_role(uint64_t id);
std::string reference_cardinality(uint64_t id);
std::string reference_validation_hint(uint64_t id);
std::string reference_report_section(uint64_t id);
void attach_reference_detail(Movie& movie);
std::string reference_codec_private_shape(const std::string& codec);
std::string reference_codec_risk_note(const std::string& codec);
unsigned reference_codec_default_priority(const std::string& codec);
void attach_codec_reference_detail(Movie& movie);
std::string reference_language_family(const std::string& language);
std::string reference_language_display(const std::string& language);
void attach_language_reference(Movie& movie);
std::string reference_mime_family(const std::string& mime);
void attach_mime_reference(Movie& movie);
std::string reference_extension_family(const std::string& ext);
void attach_extension_reference(Movie& movie);
void attach_reference_summary(Movie& movie);
}
