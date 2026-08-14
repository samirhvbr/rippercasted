#pragma once

/// rippercasted — a modern C++ utility library.
///
/// @file rippercasted.hpp
/// @brief Public header — include this to use the library.

#include <string>
#include <string_view>
#include <cstdint>
#include <vector>

namespace rippercasted {

/// Library version info.
struct Version {
    static constexpr std::uint8_t major = 0;
    static constexpr std::uint8_t minor = 1;
    static constexpr std::uint8_t patch = 0;

    /// Returns "0.1.0" style string.
    static std::string string();
};

/// Returns the library name.
std::string_view name();

/// Returns the library version string.
std::string_view version_string();

/// A simple string caster — wraps a value in a friendly representation.
///
/// Useful as a demo of the library's public API.
class Caster {
public:
    Caster() = default;
    explicit Caster(std::string tag);

    /// Sets the tag prefix shown in cast output.
    void set_tag(std::string tag);

    /// Returns the current tag.
    std::string_view tag() const;

    /// Casts an integer to a string with the tag prefix.
    std::string cast(int value) const;

    /// Casts a double to a string with the tag prefix.
    std::string cast(double value) const;

    /// Casts a generic string with the tag prefix.
    std::string cast(std::string_view value) const;

private:
    std::string tag_ = "rippercasted";
};

}  // namespace rippercasted
