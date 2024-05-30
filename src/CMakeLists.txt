find_package(fmt REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(WAYLAND_CLIENT REQUIRED wayland-client)
pkg_search_module(XKBCOMMON REQUIRED xkbcommon)
pkg_search_module(LILV REQUIRED lilv-0)
pkg_search_module(LV2 REQUIRED lv2)

file(GLOB_RECURSE PLUGIN_TORTURE_SOURCES *.cpp)

add_executable(plugintorture ${PLUGIN_TORTURE_SOURCES})

target_include_directories(plugintorture
  PUBLIC
    ${LILV_INCLUDE_DIRS}
    ${LV2_INCLUDE_DIRS})

target_link_libraries(plugintorture
  PUBLIC
    fmt::fmt
    ${WAYLAND_CLIENT_LINK_LIBRARIES}
    ${XKBCOMMON_LINK_LIBRARIES}
    ${LILV_LINK_LIBRARIES}
    ${LV2_LINK_LIBRARIES})
