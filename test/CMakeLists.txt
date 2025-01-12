cmake_minimum_required(VERSION 3.15)
project(LVGLEx)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(.. ${CMAKE_CURRENT_BINARY_DIR}/third_party)

add_executable(test_helloworld helloworld/main.cpp)
target_link_libraries(test_helloworld PRIVATE LVGLEx-static)

