enable_testing()
cmake_minimum_required(VERSION 3.16)

project(ActionCenter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Finding packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GTKLAYER REQUIRED gtk4-layer-shell-0)

# Includes
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)
include_directories(${JSONCPP_INCLUDE_DIRS})

add_subdirectory(tests)
add_subdirectory(src)

