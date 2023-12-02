cmake_minimum_required(VERSION 3.15...3.26)

project(B_TREE VERSION 0.1.00)

add_subdirectory(src)

add_executable(B_tree_test src/test.cpp)
target_link_libraries(B_tree_test PRIVATE B_tree)
target_compile_features(B_tree_test PRIVATE cxx_std_20)
# target_include_directories(test PRIVATE)
