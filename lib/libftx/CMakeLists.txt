cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CACHEFILE_DIR}/cmake")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)

project(libftx C)

find_package(SDL2 REQUIRED)
link_directories(${SDL2_LIBRARY_DIRS})

set(libftx_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(libftx_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(libftx_SRCS
	${libftx_SRC_DIR}/hit.c
	${libftx_SRC_DIR}/line.c
	${libftx_SRC_DIR}/math.c
	${libftx_SRC_DIR}/point.c)
file(GLOB_RECURSE libftx_HDRS ${libftx_HDRS} ${libftx_INC_DIR}/libftx/*.h)
set(libftx_HDR ${libftx_INC_DIR}/libftx.h)

add_library(ftx ${libftx_SRCS} ${libftx_HDRS} ${libftx_HDR})
target_include_directories(ftx PUBLIC ${libftx_INC_DIR} ${SDL2_INCLUDE_DIRS})
target_link_libraries(ftx PUBLIC ft ${SDL2_LIBRARY})
add_dependencies(ftx ft)
target_compile_options(ftx PUBLIC -Wall -Werror -Wextra -ansi)

set_target_properties(ftx PROPERTIES OUTPUT_NAME "ftx")
set_target_properties(ftx PROPERTIES OUTPUT_NAME_DEBUG "ftx.dev")
set_target_properties(ftx PROPERTIES OUTPUT_NAME_SAN "ftx.san")
set_target_properties(ftx PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_LIST_DIR})

if (APPLE)
	include_directories("/System/Library/Frameworks")
	find_library(COCOA_LIBRARIES Cocoa)
	find_library(IOKIT_LIBRARIES IOkit)
	find_library(COREVIDEO_LIBRARIES CoreVideo)
	target_link_libraries(ftx PUBLIC
		"-framework AppKit" "-framework OpenGL"
		"-framework IOKit" "-framework CoreVideo")
endif ()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")
if (CMAKE_C_FLAGS_RELEASE MATCHES "-O3")
	string(REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif ()
if (CMAKE_BUILD_TYPE MATCHES San)
	set_target_properties(ftx PROPERTIES COMPILE_FLAGS "-fsanitize=address")
	set_target_properties(ftx PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()

install(FILES ${libftx_HDRS} DESTINATION include/libftx)
install(FILES ${libftx_HDR} DESTINATION include)
