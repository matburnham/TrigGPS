cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} src/TrigGPS)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests
  src/TrigGPS/pmrrc.cpp
  #src/TrigGPS/search.cpp
  test/tests.cpp
  test/test_pmrrc.cpp
  #test/test_search.cpp
)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
