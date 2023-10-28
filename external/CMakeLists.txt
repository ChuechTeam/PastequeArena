# Adding Raylib
# Based of https://github.com/SasLuca/raylib-cmake-template/blob/master/CMakeLists.txt
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied example games
set(OPENGL_VERSION "3.3" CACHE STRING "" FORCE) # use OpenGL 3.3
FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "4.5.0"
        GIT_PROGRESS TRUE
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib"
)

FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY "https://github.com/RobLoach/raylib-cpp"
        GIT_TAG "v4.5.2"
        GIT_PROGRESS TRUE
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/raylib_cpp"
)

FetchContent_MakeAvailable(raylib_cpp)