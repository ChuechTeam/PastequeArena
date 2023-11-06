cmake_minimum_required(VERSION 3.21)
project(PastequeArena CXX)

include(CMakeOptions.cmake)
include(cmake/OSInfo.cmake)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

# Add all cpp files using glob recurse.
# Now, people say that it is bad and evil for various reasons, but now
# that we have CONFIGURE_DEPENDS which should make CMake break *less*,
# why not give it a shot?
# Also, that enables people using generated Visual Studio sln files
# to add files without having to re-run CMake.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
# This is only necessary for convenience in Visual Studio,
# no need for CONFIGURE_DEPENDS as this only needs to be refreshed
# at generation time (running cmake ..).
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    file(GLOB_RECURSE HEADERS src/*.h)
else ()
    set(HEADERS) # Empty
endif ()

if (${PLATFORM} STREQUAL "Android")
    add_library(PastequeArena SHARED ${SOURCES} ${HEADERS})
else ()
    add_executable(PastequeArena ${SOURCES} ${HEADERS})
endif ()

# -----------------
# COMPILER SETUP
# -----------------

target_include_directories(PastequeArena PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src" "${CMAKE_CURRENT_LIST_DIR}/external/raygui")
target_link_libraries(PastequeArena raylib raylib_cpp)

# Precompile headers that are often used, and rarely changed.
# Usually, external libraries and std headers are put there,
# especially when they are included in a commonly-used header (such as Engine.h).
target_precompile_headers(PastequeArena PRIVATE
        <raylib-cpp.hpp>
        <raygui.h>
        <filesystem>
        <array>
        <vector>
        <cstdint>)

if (MSVC)
    target_compile_options(PastequeArena PRIVATE /fp:fast /W3)
    target_compile_definitions(PastequeArena PRIVATE _CRT_SECURE_NO_WARNINGS=1 UNICODE=1)
endif ()

if (UNIX)
    target_link_libraries(PastequeArena m)
endif ()

if (${PLATFORM} STREQUAL "Android")
    # I don't really know why, but this symbol is NOT exported by default.
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
endif ()

# Fix for Android on CLion
if (${PLATFORM} STREQUAL "Android")
    if (CMAKE_ANDROID_ARCH_ABI STREQUAL "armeabi-v7a")
        target_compile_options(raylib PUBLIC "--target=armv7-none-linux-androideabi${CMAKE_SYSTEM_VERSION}")
    elseif (CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
        target_compile_options(raylib PUBLIC "--target=aarch64-none-linux-android${CMAKE_SYSTEM_VERSION}")
    endif ()
endif ()

# -----------------
# ASSETS HANDLING
# -----------------

target_compile_definitions(PastequeArena PRIVATE PA_PACKAGED=${PA_PACKAGED})
if (PA_PACKAGED)
    # TODO?
else ()
    set(ASSETS_DIR "${CMAKE_CURRENT_LIST_DIR}/assets")
    target_compile_definitions(PastequeArena PRIVATE PA_DEV_ASSETS_DIR="${ASSETS_DIR}")
endif ()

# -----------------
# OS INFO
# -----------------

register_os_macros(PastequeArena)