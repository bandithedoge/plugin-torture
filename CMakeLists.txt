cmake_minimum_required(VERSION 3.20)
project(plugintorture)
set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(glfw)

set(Q_BUILD_EXAMPLES OFF)
set(Q_BUILD_TEST OFF)
add_subdirectory(q)

include_directories(
  PUBLIC
    imgui
)

add_subdirectory(src)
add_subdirectory(imgui)

target_link_libraries(imgui
  PUBLIC
    glfw)

target_link_libraries(plugintorture
  PUBLIC
    libq
    libqio
    glfw
    imgui)
