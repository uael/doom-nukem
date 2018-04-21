cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CACHEFILE_DIR}/cmake")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

project(wolf3d C)

set(wolf3d_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(wolf3d_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE wolf3d_SRCS ${wolf3d_SRCS} ${wolf3d_SRC_DIR}/*.c)
file(GLOB_RECURSE wolf3d_HDRS ${wolf3d_HDRS} ${wolf3d_INC_DIR}/wolf3d/*.h)
set(wolf3d_HDR ${wolf3d_INC_DIR}/wolf3d.h)

add_subdirectory(ext)
add_executable(wolf3d ${wolf3d_SRCS} ${wolf3d_HDRS} ${wolf3d_HDR})
target_include_directories(wolf3d PUBLIC ${wolf3d_INC_DIR})
target_link_libraries(wolf3d PUBLIC ft ftx)
add_dependencies(wolf3d ft)

target_compile_options(wolf3d
  PUBLIC -Wall -Werror -Wextra
  PUBLIC -fomit-frame-pointer -ansi
  PUBLIC -Wno-missing-field-initializers)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")
if(CMAKE_C_FLAGS_RELEASE MATCHES "-O3")
  string(REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif()
if (CMAKE_BUILD_TYPE MATCHES San)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")
endif ()

install(FILES ${wolf3d_HDRS} DESTINATION include/wolf3d)
install(FILES ${wolf3d_HDR} DESTINATION include)