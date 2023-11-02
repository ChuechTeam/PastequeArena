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
        URL "https://github.com/raysan5/raylib/archive/refs/tags/4.5.0.zip"
        URL_HASH SHA256=32c25fed7cee561b9aa2614b4edd029c6baf3d2e7dba69d51e52da17a567e319
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib"
        DOWNLOAD_DIR "${CMAKE_CURRENT_LIST_DIR}/_downloads/raylib"
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
FetchContent_MakeAvailable(raylib)

# Adding Raylib C++

FetchContent_Declare(
        raylib_cpp
        URL "https://github.com/RobLoach/raylib-cpp/archive/refs/tags/v4.5.2.zip"
        URL_HASH SHA256=391ffdebc1a057351ec7508bfc13803afe0ede3ef3a127f5c4916951c0a49950
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib_cpp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_LIST_DIR}/_downloads/raylib_cpp"
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

FetchContent_MakeAvailable(raylib_cpp)