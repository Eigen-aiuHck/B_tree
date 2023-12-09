add_library(B_tree STATIC ${CMAKE_CURRENT_SOURCE_DIR}/b_tree/b_tree.cpp)

target_compile_features(B_tree PRIVATE cxx_std_20)
target_include_directories(B_tree PUBLIC ${PROJECT_SOURCE_DIR}/include)
