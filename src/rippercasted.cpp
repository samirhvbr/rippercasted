/// rippercasted — implementation file.
///
/// @file rippercasted.cpp
/// @brief Implementation of the public API declared in rippercasted.hpp.

#include "rippercasted/rippercasted.hpp"

#include <sstream>
#include <iomanip>

namespace rippercasted {

// ---- Version ----------------------------------------------------------------

std::string Version::string() {
    return std::to_string(major) + "." +
           std::to_string(minor) + "." +
           std::to_string(patch);
}

std::string_view name() {
    return "rippercasted";
}

std::string_view version_string() {
    static const std::string v = Version::string();
    return v;
}

// ---- Caster -----------------------------------------------------------------

Caster::Caster(std::string tag) : tag_(std::move(tag)) {}

void Caster::set_tag(std::string tag) {
    tag_ = std::move(tag);
}

std::string_view Caster::tag() const {
    return tag_;
}

std::string Caster::cast(int value) const {
    std::ostringstream oss;
    oss << "[" << tag_ << "] int:" << value;
    return oss.str();
}

std::string Caster::cast(double value) const {
    std::ostringstream oss;
    oss << "[" << tag_ << "] double:" << std::fixed << std::setprecision(4) << value;
    return oss.str();
}

std::string Caster::cast(std::string_view value) const {
    std::ostringstream oss;
    oss << "[" << tag_ << "] str:\"" << value << "\"";
    return oss.str();
}

}  // namespace rippercasted
