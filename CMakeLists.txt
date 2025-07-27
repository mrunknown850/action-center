cmake_minimum_required(VERSION 3.16)

project(ActionCenter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(ENV{PKG_CONFIG_PATH} "/usr/lib/pkgconfig:/usr/share/pkgconfig")

# Finding packages
find_package(jsoncpp CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GTKLAYER REQUIRED gtk4-layer-shell-0)

# Builds
include_directories(
 include
)

file(GLOB_RECURSE APP_SRC
  src/Config/*.cpp
  src/UI/*.cpp
  src/Plugin/*.cpp
  src/*.cpp
)

add_executable(ac ${APP_SRC})

# Linker
# Gtk-layer-shell (system)
target_include_directories(ac PRIVATE ${GTKLAYER_INCLUDE_DIRS})
target_link_directories(ac PRIVATE ${GTKLAYER_LIBRARY_DIRS})
target_link_libraries(ac PRIVATE ${GTKLAYER_LIBRARIES})

# GTKmm (system)
target_include_directories(ac PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(ac PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(ac PRIVATE ${GTKMM_LIBRARIES})

# JSONCPP (vcpkg)
target_link_libraries(ac PRIVATE jsoncpp)

