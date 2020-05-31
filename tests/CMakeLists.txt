cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
)
FetchContent_MakeAvailable(doctest)

add_executable(dbg_test tests.cc)
add_test(dbg_test dbg_test)
target_link_libraries(dbg_test dbg::dbg doctest::doctest)