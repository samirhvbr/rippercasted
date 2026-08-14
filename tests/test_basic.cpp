/// Minimal smoke test for rippercasted — no external test framework required.

#include "rippercasted/rippercasted.hpp"

#include <cassert>
#include <iostream>
#include <string>

namespace {

int failures = 0;

void check(bool cond, const std::string& msg) {
    if (!cond) {
        std::cerr << "FAIL: " << msg << '\n';
        ++failures;
    } else {
        std::cout << "ok:   " << msg << '\n';
    }
}

}  // namespace

int main() {
    using namespace rippercasted;

    check(name() == "rippercasted", "name() returns rippercasted");
    check(version_string() == "0.1.0", "version_string() returns 0.1.0");
    check(Version::string() == "0.1.0", "Version::string() returns 0.1.0");

    Caster c;
    check(c.tag() == "rippercasted", "default tag is rippercasted");

    c.set_tag("unit");
    check(c.tag() == "unit", "tag updated to unit");

    check(c.cast(42).find("int:42") != std::string::npos, "cast(int) contains value");
    check(c.cast(2.5).find("double:") != std::string::npos, "cast(double) contains type marker");
    check(c.cast("hi").find("str:\"hi\"") != std::string::npos, "cast(string_view) contains quoted value");

    if (failures == 0) {
        std::cout << "\nAll tests passed.\n";
        return 0;
    }
    std::cerr << "\n" << failures << " test(s) failed.\n";
    return 1;
}
