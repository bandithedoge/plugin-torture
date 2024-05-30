find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE IMGUI_SOURCES *.cpp)

add_library(imgui ${IMGUI_SOURCES})

target_include_directories(imgui
  PUBLIC
    .)

target_link_libraries(imgui
  PUBLIC
    Freetype::Freetype
    OpenGL::GL)
