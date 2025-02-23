cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0077 NEW)

project(LVGLEx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

set(LVGL_CFG_TEMPLATE_HEADER ${CMAKE_CURRENT_LIST_DIR}/privately/lv_conf_template.h.in)
include(cmake/base.cmake)
include(cmake/SDL.cmake)
include(cmake/freetype2.cmake)
include(cmake/lvgl.cmake)
include(cmake/fmt.cmake)

file(GLOB_RECURSE LVGLEX_RESOURCES
    src/*.cpp
)

add_library(LVGLEx-static STATIC ${LVGLEX_RESOURCES})
target_include_directories(LVGLEx-static PRIVATE privately)
target_compile_definitions(LVGLEx-static PRIVATE LVGLEX_IS_MODEL=1)
target_link_libraries(LVGLEx-static PUBLIC ${CPPMODULE_LINK_LIBRARIES_ALL})
target_include_directories(LVGLEx-static PUBLIC cmake_include_interface ${CMAKE_CURRENT_LIST_DIR}/include)