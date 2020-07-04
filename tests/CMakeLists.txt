cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
)
FetchContent_MakeAvailable(doctest)

add_executable(dbg_test tests.cc)
add_test(dbg_test dbg_test)
target_link_libraries(dbg_test PRIVATE dbg::dbg doctest::doctest)

find_package(range-v3)
if (range-v3_FOUND)
  message(STATUS "Testing with range-v3")
  target_link_libraries(dbg_test PRIVATE range-v3::range-v3)
endif ()
