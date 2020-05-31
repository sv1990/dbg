cmake_minimum_required(VERSION 3.14)

project(PrintableAny CXX)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type set. Defaulting to RELEASE")
  set(CMAKE_BUILD_TYPE Release)
else ()
  message(STATUS "Using build type ${CMAKE_BUILD_TYPE}")
endif ()

add_library(dbg INTERFACE)
add_library(dbg::dbg ALIAS dbg)
target_compile_features(dbg INTERFACE cxx_std_20)
target_include_directories(
  dbg
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakeDependentOption)
cmake_dependent_option(
  DBG_ENABLE_TESTS
  "Enable tests"
  ON
  "${is_subproject}"
  OFF
)

if (DBG_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif ()