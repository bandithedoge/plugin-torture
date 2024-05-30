cmake_minimum_required(VERSION 3.20)
project(plugintorture)
set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(glfw)
add_subdirectory(portaudio)

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
    PortAudio
    glfw
    imgui)
