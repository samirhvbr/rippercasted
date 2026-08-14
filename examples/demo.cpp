/// Demo program showing how to consume the rippercasted library.

#include "rippercasted/rippercasted.hpp"

#include <iostream>

int main() {
    std::cout << "== " << rippercasted::name()
              << " v" << rippercasted::version_string() << " ==\n";

    rippercasted::Caster caster("demo");

    std::cout << caster.cast(42)            << '\n';
    std::cout << caster.cast(3.14159)       << '\n';
    std::cout << caster.cast("hello world") << '\n';

    caster.set_tag("custom");
    std::cout << caster.cast(7) << '\n';

    return 0;
}
