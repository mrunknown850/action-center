file(GLOB_RECURSE APP_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/Config/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Plugin/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)


add_executable(action-center ${APP_SRC})

# Linker
# Gtk-layer-shell (system)
target_include_directories(action-center PRIVATE ${GTKLAYER_INCLUDE_DIRS})
target_link_directories(action-center PRIVATE ${GTKLAYER_LIBRARY_DIRS})
target_link_libraries(action-center PRIVATE ${GTKLAYER_LIBRARIES})

# GTKmm (system)
target_include_directories(action-center PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(action-center PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(action-center PRIVATE ${GTKMM_LIBRARIES})

# JSONCPP (vcpkg)
target_link_libraries(action-center PRIVATE ${JSONCPP_LIBRARIES})

# Others

