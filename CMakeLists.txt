cmake_minimum_required(VERSION 3.8)

project(countbits_project CXX)

find_package(GTest REQUIRED)

add_executable(countbits_test src/main/countbits.cc src/test/countbits_test.cc)

set_target_properties(countbits_test PROPERTIES LINKER_LANGUAGE CXX)

target_compile_options(countbits_test PUBLIC -std=c++11 -Wall -Wfloat-conversion)

target_include_directories(countbits_test PUBLIC
  src/main
  ${GTEST_INCLUDE_DIRS} # doesn't do anything on Linux
)

target_link_libraries(countbits_test PUBLIC ${GTEST_LIBRARIES})
