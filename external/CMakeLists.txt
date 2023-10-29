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
    message(STATUS "Building for Android!!! YAY")
    set(PLATFORM "Android" CACHE STRING " " FORCE) # build for Android
    set(ANDROID_NDK ${CMAKE_ANDROID_NDK} CACHE STRING " " FORCE) # fix the NDK
else()
    set(OPENGL_VERSION "3.3" CACHE STRING " " FORCE) # use OpenGL 3.3
    endif()
message(STATUS "system name ${CMAKE_SYSTEM_NAME} ")

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "4.5.0"
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib"

)
FetchContent_MakeAvailable(raylib)

# Adding Raylib C++

FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY "https://github.com/RobLoach/raylib-cpp"
        GIT_TAG "v4.5.2"
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib_cpp"
)

FetchContent_MakeAvailable(raylib_cpp)