cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

project(wolf3d C)

find_package(SDL2 REQUIRED)
link_directories(${SDL2_LIBRARY_DIRS})

set(wolf3d_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(wolf3d_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE wolf3d_SRCS ${wolf3d_SRCS} ${wolf3d_SRC_DIR}/*.c)
file(GLOB_RECURSE wolf3d_HDRS ${wolf3d_HDRS} ${wolf3d_INC_DIR}/wolf3d/*.h)
set(wolf3d_HDR ${wolf3d_INC_DIR}/wolf3d.h)

add_subdirectory(ext)
add_executable(wolf3d ${wolf3d_SRCS} ${wolf3d_HDRS} ${wolf3d_HDR})
target_include_directories(wolf3d PUBLIC ${wolf3d_INC_DIR})
target_link_libraries(wolf3d PUBLIC ft ftx ${SDL2_LIBRARY})
add_dependencies(wolf3d ft ftx)

if (APPLE)
	include_directories("/System/Library/Frameworks")
	find_library(COCOA_LIBRARIES Cocoa)
	find_library(IOKIT_LIBRARIES IOkit)
	find_library(COREVIDEO_LIBRARIES CoreVideo)
	target_link_libraries(wolf3d PUBLIC
		"-framework AppKit" "-framework OpenGL"
		"-framework IOKit" "-framework CoreVideo")
endif ()

target_compile_options(wolf3d
	PUBLIC -Wall -Werror -Wextra
	PUBLIC -fomit-frame-pointer -ansi
	PUBLIC -Wno-missing-field-initializers)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")
if (CMAKE_C_FLAGS_RELEASE MATCHES "-O3")
	string(REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif ()
if (CMAKE_BUILD_TYPE MATCHES San)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")
endif ()

install(FILES ${wolf3d_HDRS} DESTINATION include/wolf3d)
install(FILES ${wolf3d_HDR} DESTINATION include)
