cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)

project(wolf3d C)

find_package(SDL2 REQUIRED)
link_directories(${SDL2_LIBRARY_DIRS})

set(wolf3d_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(wolf3d_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(wolf3d_SRCS
	${wolf3d_SRC_DIR}/main.c)
file(GLOB_RECURSE wolf3d_HDRS ${wolf3d_HDRS} ${wolf3d_INC_DIR}/wolf3d/*.h)
set(wolf3d_HDR ${wolf3d_INC_DIR}/wolf3d.h)

add_subdirectory(lib)
add_executable(wolf3d ${wolf3d_SRCS} ${wolf3d_HDRS} ${wolf3d_HDR})
target_include_directories(wolf3d PUBLIC ${wolf3d_INC_DIR})
target_link_libraries(wolf3d PUBLIC ft ftx ${SDL2_LIBRARY})
add_dependencies(wolf3d ft ftx)
target_compile_options(wolf3d PUBLIC -Wall -Werror -Wextra -ansi)

set_target_properties(wolf3d PROPERTIES OUTPUT_NAME "wolf3d")
set_target_properties(wolf3d PROPERTIES OUTPUT_NAME_DEBUG "wolf3d.dev")
set_target_properties(wolf3d PROPERTIES OUTPUT_NAME_SAN "wolf3d.san")
set_target_properties(wolf3d PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_LIST_DIR})

if (APPLE)
	include_directories("/System/Library/Frameworks")
	find_library(COCOA_LIBRARIES Cocoa)
	find_library(IOKIT_LIBRARIES IOkit)
	find_library(COREVIDEO_LIBRARIES CoreVideo)
	target_link_libraries(wolf3d PUBLIC
		"-framework AppKit" "-framework OpenGL"
		"-framework IOKit" "-framework CoreVideo")
endif ()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")
if (CMAKE_C_FLAGS_RELEASE MATCHES "-O3")
	string(REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif ()
if (CMAKE_BUILD_TYPE MATCHES San)
	set_target_properties(wolf3d PROPERTIES COMPILE_FLAGS "-fsanitize=address")
	set_target_properties(wolf3d PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()

install(FILES ${wolf3d_HDRS} DESTINATION include/wolf3d)
install(FILES ${wolf3d_HDR} DESTINATION include)
