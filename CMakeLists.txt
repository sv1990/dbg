cmake_minimum_required(VERSION 3.14)

project(PrintableAny CXX)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type set. Defaulting to RELEASE")
  set(CMAKE_BUILD_TYPE Release)
else ()
  message(STATUS "Using build type ${CMAKE_BUILD_TYPE}")
endif ()

add_executable(dbg main.cc)
target_compile_features(dbg PRIVATE cxx_std_20)
target_compile_options(dbg PRIVATE "-Wall;-Wextra;-pedantic")

