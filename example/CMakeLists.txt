cmake_minimum_required(VERSION 3.14)

add_executable(example example.cc)
target_compile_features(example PRIVATE cxx_std_20)
target_link_libraries(example PRIVATE dbg::dbg)
