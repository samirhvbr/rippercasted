cmake_minimum_required(VERSION 3.16)
project(rippercasted
    VERSION 0.1.0
    DESCRIPTION "A modern C++ library — fast, sharp, and cast into reality."
    LANGUAGES CXX
)

# ---- Build options -----------------------------------------------------------
option(RIPPERCASTED_BUILD_EXAMPLES "Build rippercasted examples" ON)
option(RIPPERCASTED_BUILD_TESTS    "Build rippercasted tests"    ON)
option(RIPPERCASTED_INSTALL        "Generate install targets"    ON)

# ---- C++ standard ------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ---- Default install paths ---------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ---- Library target ----------------------------------------------------------
add_library(rippercasted STATIC)
add_library(rippercasted::rippercasted ALIAS rippercasted)

target_include_directories(rippercasted
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(rippercasted
    PRIVATE
        src/rippercasted.cpp
)

target_compile_features(rippercasted PUBLIC cxx_std_17)

# Warnings for the library itself
if(MSVC)
    target_compile_options(rippercasted PRIVATE /W4 /permissive-)
else()
    target_compile_options(rippercasted PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    )
endif()

# ---- Examples ----------------------------------------------------------------
if(RIPPERCASTED_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ---- Tests -------------------------------------------------------------------
if(RIPPERCASTED_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ---- Install -----------------------------------------------------------------
if(RIPPERCASTED_INSTALL)
    install(TARGETS rippercasted
        EXPORT rippercastedTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(DIRECTORY include/rippercasted
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(EXPORT rippercastedTargets
        FILE rippercastedTargets.cmake
        NAMESPACE rippercasted::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rippercasted
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/rippercastedConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/rippercastedConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/rippercastedConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rippercasted
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/rippercastedConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/rippercastedConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rippercasted
    )
endif()
