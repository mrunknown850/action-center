# ============== TESTINGS =============
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# set_target_properties(gtest PROPERTIES CXX_CLANG_TIDY "")
# set_target_properties(gtest_main PROPERTIES CXX_CLANG_TIDY "")


file(GLOB_RECURSE APP_TEST_SRC
  ${CMAKE_SOURCE_DIR}/Config/*.cpp
)

file(GLOB_RECURSE TEST_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(
  run_tests ${APP_TEST_SRC} ${TEST_SRC}
)

# set_target_properties(run_tests PROPERTIES CXX_CLANG_TIDY "")
target_include_directories(run_tests PRIVATE ${GTKLAYER_INCLUDE_DIRS})
target_link_directories(run_tests PRIVATE ${GTKLAYER_LIBRARY_DIRS})
target_link_libraries(run_tests PRIVATE ${GTKLAYER_LIBRARIES})

# GTKmm (system)
target_include_directories(run_tests PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(run_tests PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(run_tests PRIVATE ${GTKMM_LIBRARIES})

# JSONCPP (vcpkg)
target_link_libraries(run_tests PRIVATE ${JSONCPP_LIBRARIES})

# GTest
include(GoogleTest)
target_link_libraries(run_tests PRIVATE GTest::gtest_main)
# get_target_property(GTEST_INCLUDE_DIRS GTest::gtest_main INTERFACE_INCLUDE_DIRECTORIES)
# target_include_directories(run_tests SYSTEM PRIVATE ${GTEST_INCLUDE_DIRS})
gtest_discover_tests(
  run_tests
  PROPERTIES VERBOSE 1
)

