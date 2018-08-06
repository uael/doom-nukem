# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#              #
#    Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(wolf3d VERSION 0.0.1 LANGUAGES C)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

## ************************************************************************** ##
# Build types
##
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

## ************************************************************************** ##
# Options
##


## ************************************************************************** ##
# Dependencies
##
add_subdirectory(lib)
set(__DEPS libft)
find_package(SDL2 REQUIRED)
link_directories(${SDL2_LIBRARY_DIRS})
set(__DEPS ${__DEPS} "${SDL2_LIBRARY}")
if (APPLE)
	include_directories("/System/Library/Frameworks")
	find_library(COCOA_LIBRARIES Cocoa)
	find_library(IOKIT_LIBRARIES IOkit)
	find_library(COREVIDEO_LIBRARIES CoreVideo)
	set(__DEPS ${__DEPS} "-framework AppKit" "-framework OpenGL")
	set(__DEPS ${__DEPS} "-framework IOKit" "-framework CoreVideo")
endif ()
find_package(Threads REQUIRED)
set(__DEPS ${__DEPS} Threads::Threads)

## ************************************************************************** ##
# Project directories definition
##
set(__INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(__SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

## ************************************************************************** ##
# Target
##
add_executable(wolf3d
	${__SRC_DIR}/main.c)
add_dependencies(wolf3d libft)

set_target_properties(wolf3d PROPERTIES
	C_STANDARD 90
	OUTPUT_NAME "wolf3d"
	OUTPUT_NAME_DEBUG "wolf3d.dev"
	OUTPUT_NAME_SAN "wolf3d.san"
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(wolf3d
	PRIVATE ${__SRC_DIR}
	PUBLIC ${__INC_DIR} ${SDL2_INCLUDE_DIR} "C:/Users/uael/SDL2/include")
if (MSVC)
	target_link_libraries(wolf3d PUBLIC ${__DEPS})
	target_compile_definitions(wolf3d PRIVATE _CRT_SECURE_NO_WARNINGS)
	target_compile_options(wolf3d PRIVATE /Oy /W3)
else ()
	target_link_libraries(wolf3d
		PUBLIC ${__DEPS}
		PRIVATE
			$<$<CONFIG:San>:-fsanitize=address>
			$<$<CONFIG:San>:-fno-omit-frame-pointer>)
	target_compile_options(wolf3d
		PRIVATE
			-Wall -Werror -Wextra
			-ansi -fomit-frame-pointer
			-Wno-missing-field-initializers
			$<$<CONFIG:Debug>:-g3 -O0>
			$<$<CONFIG:San>:-g3 -O0 -fsanitize=address>)
endif ()

if (CMAKE_C_FLAGS_RELEASE MATCHES "-O3")
	string(REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif ()
