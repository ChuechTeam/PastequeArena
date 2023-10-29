cmake_minimum_required(VERSION 3.21)
project(PastequeArena CXX)	

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)

set(SOURCES
        src/main.cpp)

if (${PLATFORM} STREQUAL "Android")
    add_library(PastequeArena SHARED ${SOURCES})
else()
    add_executable(PastequeArena ${SOURCES})
endif ()

target_include_directories(PastequeArena PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src" "${CMAKE_CURRENT_LIST_DIR}/external/raygui")
target_link_libraries(PastequeArena raylib raylib_cpp)

target_compile_definitions(PastequeArena PRIVATE RAYGUI_IMPLEMENTATION=1)

STRING(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")

if (MSVC)
    target_compile_options(PastequeArena PRIVATE /fp:fast /W3)
    target_compile_definitions(PastequeArena PRIVATE _CRT_SECURE_NO_WARNINGS=1)
endif ()

if (UNIX)
    target_link_libraries(PastequeArena m)
endif ()

if (${PLATFORM} STREQUAL "Android")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
endif()