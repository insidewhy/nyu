cmake_minimum_required(VERSION 2.6)

set(CHILON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../chilon)
set(CMAKE_MODULE_PATH ${CHILON_DIR}/cmake/modules)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

project(nyu)

include(C++0x)
include(Installer)

include_directories(..)
add_definitions(-Wall)

add_executable(nyu nyu.cpp options.cpp
               cpp/build_class.cpp cpp/output_file.cpp cpp/builder.cpp
               cpp/build_module.cpp cpp/get_type_and_value.cpp
               cpp/scope_ref_cache.cpp cpp/build_grammar.cpp
               cpp/get_grammar.cpp cpp/build_rule.cpp)

install(TARGETS nyu
        RUNTIME DESTINATION ${BIN_DIR}
        LIBRARY DESTINATION ${LIB_DIR})
file(GLOB headers *.hpp)
install(FILES ${headers} DESTINATION ${HEADER_DIR}/nyu)

set(MOUSEDEER_SYSTEM_INCLUDE_PATH
    "${CMAKE_INSTALL_PREFIX}/include/nyu"
    CACHE STRING "nyu default include path")

configureFile(config.hpp)
