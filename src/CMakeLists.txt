cmake_minimum_required(VERSION 3.14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_NAME "cpp_rtklib")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
project(${PROJECT_NAME} LANGUAGES C CXX VERSION 0.0.1)

set(DEFS)
set(CFLAGS -Wall -pedantic)
set(LDLIBS tbb pthread)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/RTKLIB ${CMAKE_CURRENT_BINARY_DIR}/RTKLIB)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rinex)

add_library(cpp_rtklib_Lib)
target_sources(cpp_rtklib_Lib
    PRIVATE
        include_c/rtklib.h
        include_c/rinex_c.h
        cpp_rtklib.cpp
    PUBLIC
        cpp_rtklib.h
)

target_compile_features(cpp_rtklib_Lib PUBLIC cxx_std_20)
target_compile_options(cpp_rtklib_Lib PRIVATE ${CFLAGS})
target_compile_definitions(cpp_rtklib_Lib PRIVATE ${DEFS})
target_link_libraries(cpp_rtklib_Lib ${LDLIBS})
target_include_directories(cpp_rtklib_Lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include_c)
#target_include_directories(cpp_rtklib_Lib PUBLIC ${INSTALL_DIR}/include)

add_executable(cpp_rtklib main.cpp)
target_link_libraries(cpp_rtklib cpp_rtklib_Lib $<TARGET_FILE:cpp_rtklib_rinex_Lib>)

# install(TARGETS cpp_rtklib
# 	EXPORT cpp_rtklib
# )

set_target_properties(cpp_rtklib_Lib PROPERTIES
  PUBLIC_HEADER cpp_rtklib.h
  OUTPUT_NAME "cpp_rtklib"
)