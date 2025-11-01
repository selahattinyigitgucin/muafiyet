cmake_minimum_required(VERSION 3.16)
project(muafiyet)
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/lib/raylib")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
add_subdirectory(${RAYLIB_DIR} raylib_build)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(
${PROJECT_NAME} PRIVATE raylib
)
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt X11 GL)
endif()