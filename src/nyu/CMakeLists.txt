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
               cpp/output_file.cpp cpp/compilation_unit.cpp
               cpp/builder.cpp cpp/build_class.cpp cpp/build_rule.cpp
               cpp/build_grammar.cpp cpp/build_module.cpp
               cpp/get_type_and_value.cpp cpp/get_grammar.cpp cpp/get_class.cpp)

install(TARGETS nyu
        RUNTIME DESTINATION ${BIN_DIR}
        LIBRARY DESTINATION ${LIB_DIR})
file(GLOB headers *.hpp)
install(FILES ${headers} DESTINATION ${HEADER_DIR}/nyu)
install(DIRECTORY ${CHILON_DIR} DESTINATION ${HEADER_DIR}
        REGEX /\(.git|doc|test|bin|TODO|README\)\(/|$\) EXCLUDE)

set(MOUSEDEER_SYSTEM_INCLUDE_PATH
    "${CMAKE_INSTALL_PREFIX}/include/nyu"
    CACHE STRING "nyu default include path")

configureFile(config.hpp)
