cmake_minimum_required(VERSION 3.15)
project(LVGLEx)

set(CMAKE_CXX_STANDARD 17)

set(CPPMODULES $ENV{CPPMODULES})
set(CPPMODULE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
# 需要启用的库
set(CPPMODULE_SDL ON)
set(CPPMODULE_FREETYPE2 ON)
set(CPPMODULE_LVGL ON)
set(CPPMODULE_LVGLEX ON)
include(${CPPMODULES}/all.cmake)

add_executable(test_helloworld helloworld/main.cpp)
target_link_libraries(test_helloworld PRIVATE ${CPPMODULE_LINK_LIBRARIES_ALL})

