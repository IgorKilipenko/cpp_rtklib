cmake_minimum_required(VERSION 3.14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_NAME "cpp_rtklib_rinex")
project(${PROJECT_NAME} LANGUAGES C CXX VERSION 0.0.1)

set(DEFS)
set(CFLAGS -Wall -pedantic)
set(LDLIBS tbb pthread)

add_library(cpp_rtklib_rinex_Lib)
target_sources(cpp_rtklib_rinex_Lib
    PRIVATE
        rinex.c
        rinex.cpp
        common/date_time.cpp
        tests/datetime_test.cpp
    PUBLIC
        rinex.h
)

target_compile_features(cpp_rtklib_rinex_Lib PUBLIC cxx_std_20)
target_compile_options(cpp_rtklib_rinex_Lib PRIVATE ${CFLAGS})
target_compile_definitions(cpp_rtklib_rinex_Lib PRIVATE ${DEFS})
target_link_libraries(cpp_rtklib_rinex_Lib ${LDLIBS})
target_include_directories(cpp_rtklib_rinex_Lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include_c)

set_target_properties(cpp_rtklib_rinex_Lib PROPERTIES
  PUBLIC_HEADER rinex.h
  OUTPUT_NAME "rinex"
)