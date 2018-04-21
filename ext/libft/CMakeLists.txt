cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CACHEFILE_DIR}/cmake")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

project(libft C)

set(libft_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(libft_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE libft_SRCS ${libft_SRCS} ${libft_SRC_DIR}/*.c)
file(GLOB_RECURSE libft_HDRS ${libft_HDRS} ${libft_INC_DIR}/libft/*.h)
set(libft_HDR ${libft_INC_DIR}/libft.h)

add_library(ft ${libft_SRCS} ${libft_HDRS} ${libft_HDR})
target_include_directories(ft PUBLIC ${libft_INC_DIR})

target_compile_options(ft
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

install(FILES ${libft_HDRS} DESTINATION include/libft)
install(FILES ${libft_HDR} DESTINATION include)