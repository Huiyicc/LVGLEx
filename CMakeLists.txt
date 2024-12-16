cmake_minimum_required(VERSION 3.15)
project(LVGLEx)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE LVGLEX_RESOURCES
    src/*.cpp
)

add_library(LVGLEx-static STATIC ${LVGLEX_RESOURCES})
target_include_directories(LVGLEx-static PRIVATE privately)
target_compile_definitions(LVGLEx-static PRIVATE LVGLEX_IS_MODEL=1)
target_link_libraries(LVGLEx-static PUBLIC ${__CPPMODULE_TEMP_SDL_LIB__})
