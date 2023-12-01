cmake_minimum_required(VERSION 3.15...3.26)

project(B_TREE VERSION 0.0.01)

add_library(b_tree STATIC src/b_tree.cpp)

target_compile_features(b_tree PRIVATE cxx_std_20)

target_include_directories(b_tree PUBLIC ${CMAKE_SOURCE_DIR}/include/)

add_executable(test src/test.cpp)
target_link_libraries(test PRIVATE b_tree)
target_compile_features(test PRIVATE cxx_std_20)
# target_include_directories(test PRIVATE)
