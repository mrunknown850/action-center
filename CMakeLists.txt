cmake_minimum_required(VERSION 3.16)

project(ActionCenter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(
  include/Config
  include/Plugin
  include/UI
  include
)

file(GLOB_RECURSE APP_SRC
  src/Config/*.cpp
  src/UI/*.cpp
  src/Plugin/*.cpp
  src/*.cpp
)

add_executable(ac ${APP_SRC})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Include GTKmm include dirs
target_include_directories(ac PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(ac PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(ac PRIVATE ${GTKMM_LIBRARIES})

# Link JSONCPP via vcpkg
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(ac PRIVATE jsoncpp)

# Optionally define include dirs (vcpkg sets them automatically for jsoncpp)
# target_include_directories(ac PRIVATE ...