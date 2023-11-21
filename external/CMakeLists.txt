include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

option(ENABLE_HACKY_ANDROID_VS_TOOLCHAIN_FIX "Enable a very cursed fix for using the VS toolchain with Android" OFF)
if (ENABLE_HACKY_ANDROID_VS_TOOLCHAIN_FIX)
    macro(configure_file)
        message(STATUS "Using overridden configure_file!")
        list(APPEND subCMakeOpts "-DCMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}"
                "-DCMAKE_ANDROID_ARCH_ABI=${CMAKE_ANDROID_ARCH_ABI}"
                "-DCMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}"
                "-DCMAKE_ANDROID_NDK=${CMAKE_ANDROID_NDK}")
        _configure_file(${ARGN})
    endmacro()
endif()

# Adding Raylib
# Based of https://github.com/SasLuca/raylib-cmake-template/blob/master/CMakeLists.txt

set(BUILD_EXAMPLES OFF CACHE BOOL " " FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL " " FORCE) # don't build the supplied example games
if (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    set(PLATFORM "Android" CACHE STRING " " FORCE) # build for Android
    set(ANDROID_NDK ${CMAKE_ANDROID_NDK} CACHE STRING " " FORCE) # fix the NDK
else()
    set(OPENGL_VERSION "3.3" CACHE STRING " " FORCE) # use OpenGL 3.3
endif()

FetchContent_Declare(
        raylib
        URL "https://github.com/raysan5/raylib/archive/refs/tags/5.0.zip"
        URL_HASH SHA256=701f92f0646fbf1cec5ecc3bbc9d27d6511a3c9163c1ef8a679b15474ce854f5
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib"
        DOWNLOAD_DIR "${CMAKE_CURRENT_LIST_DIR}/_downloads/raylib"
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
FetchContent_MakeAvailable(raylib)

# Adding Raylib C++

FetchContent_Declare(
        raylib_cpp
        URL "https://github.com/RobLoach/raylib-cpp/archive/refs/tags/v5.0.0.zip"
        URL_HASH SHA256=1c6e51ac49fc805090a9bb630981010f9e118ea010c20c82b37454820ff3f143
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib_cpp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_LIST_DIR}/_downloads/raylib_cpp"
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

FetchContent_MakeAvailable(raylib_cpp)

# Add Bitsery

FetchContent_Declare(
        bitsery
        URL "https://github.com/fraillt/bitsery/archive/94f7adaf6cdcfb48e707c2750515d60c7483f8b1.zip"
        URL_HASH SHA256=003301c2c2a212718d2a1cb2b2bc4aaa071523b27fb38fe25d95232194bccf9e
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/bitsery"
        DOWNLOAD_DIR "${CMAKE_CURRENT_LIST_DIR}/_downloads/bitsery"
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
FetchContent_MakeAvailable(bitsery)