# ============== TESTINGS =============
find_package(GTest REQUIRED)

file(GLOB_RECURSE APP_TEST_SRC
  ${CMAKE_SOURCE_DIR}/Config/*.cpp
)

file(GLOB_RECURSE TEST_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(
  run_tests ${APP_TEST_SRC} ${TEST_SRC}
)

target_include_directories(run_tests PRIVATE ${GTKLAYER_INCLUDE_DIRS})
target_link_directories(run_tests PRIVATE ${GTKLAYER_LIBRARY_DIRS})
target_link_libraries(run_tests PRIVATE ${GTKLAYER_LIBRARIES})

# GTKmm (system)
target_include_directories(run_tests PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(run_tests PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(run_tests PRIVATE ${GTKMM_LIBRARIES})

# JSONCPP (vcpkg)
target_link_libraries(run_tests PRIVATE jsoncpp)

# GTest
target_link_libraries(run_tests PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(
  run_tests
  PROPERTIES VERBOSE 1
)

