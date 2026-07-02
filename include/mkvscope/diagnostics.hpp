
#pragma once
#include <string>
#include <vector>
#include <sstream>
namespace mkv {

struct Diagnostic {
 std::string stage;
 std::string message;
 unsigned severity{
};
 }
;
class Diagnostics {

    std::vector<Diagnostic> items_;

public:
    void add(std::string stage, std::string message, unsigned severity=1);

    size_t size() const {
 return items_.size();
 }

    bool empty() const {
 return items_.empty();
 }

    const std::vector<Diagnostic>& items() const {
 return items_;
 }

    std::string summary() const;

};

}
