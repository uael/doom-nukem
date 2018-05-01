cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CACHEFILE_DIR}/cmake")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)

project(libft C)

set(libft_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(libft_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(libft_SRCS
	${libft_SRC_DIR}/cty/cty.c
	${libft_SRC_DIR}/cty/cty_2.c
	${libft_SRC_DIR}/cty/cty_3.c
	${libft_SRC_DIR}/ds/alloc.c
	${libft_SRC_DIR}/ds/apd.c
	${libft_SRC_DIR}/ds/at.c
	${libft_SRC_DIR}/ds/aver.c
	${libft_SRC_DIR}/ds/back.c
	${libft_SRC_DIR}/ds/begin.c
	${libft_SRC_DIR}/ds/clean.c
	${libft_SRC_DIR}/ds/clr.c
	${libft_SRC_DIR}/ds/cpush.c
	${libft_SRC_DIR}/ds/cput.c
	${libft_SRC_DIR}/ds/ctor.c
	${libft_SRC_DIR}/ds/cusht.c
	${libft_SRC_DIR}/ds/dtor.c
	${libft_SRC_DIR}/ds/emp.c
	${libft_SRC_DIR}/ds/end.c
	${libft_SRC_DIR}/ds/grow.c
	${libft_SRC_DIR}/ds/len.c
	${libft_SRC_DIR}/ds/lst.c
	${libft_SRC_DIR}/ds/map.c
	${libft_SRC_DIR}/ds/map_2.c
	${libft_SRC_DIR}/ds/mdtor.c
	${libft_SRC_DIR}/ds/mpush.c
	${libft_SRC_DIR}/ds/mput.c
	${libft_SRC_DIR}/ds/musht.c
	${libft_SRC_DIR}/ds/nodelink.c
	${libft_SRC_DIR}/ds/nodelput.c
	${libft_SRC_DIR}/ds/noderput.c
	${libft_SRC_DIR}/ds/nodeswap.c
	${libft_SRC_DIR}/ds/nodeulink.c
	${libft_SRC_DIR}/ds/npop.c
	${libft_SRC_DIR}/ds/npush.c
	${libft_SRC_DIR}/ds/nput.c
	${libft_SRC_DIR}/ds/nrem.c
	${libft_SRC_DIR}/ds/nsht.c
	${libft_SRC_DIR}/ds/nusht.c
	${libft_SRC_DIR}/ds/pop.c
	${libft_SRC_DIR}/ds/prd.c
	${libft_SRC_DIR}/ds/push.c
	${libft_SRC_DIR}/ds/put.c
	${libft_SRC_DIR}/ds/rem.c
	${libft_SRC_DIR}/ds/set.c
	${libft_SRC_DIR}/ds/set_2.c
	${libft_SRC_DIR}/ds/sht.c
	${libft_SRC_DIR}/ds/usht.c
	${libft_SRC_DIR}/ex/ex.c
	${libft_SRC_DIR}/ex/ex_2.c
	${libft_SRC_DIR}/fs/fs.c
	${libft_SRC_DIR}/fs/fs_2.c
	${libft_SRC_DIR}/fs/fs_3.c
	${libft_SRC_DIR}/fs/fs_4.c
	${libft_SRC_DIR}/glob/glob_util
	${libft_SRC_DIR}/glob/glob_brace.c
	${libft_SRC_DIR}/glob/glob_climb_tree.c
	${libft_SRC_DIR}/glob/glob_climb_tree.h
	${libft_SRC_DIR}/glob/glob_match.c
	${libft_SRC_DIR}/glob/glob_match.h
	${libft_SRC_DIR}/glob/globux.c
	${libft_SRC_DIR}/glob/globux.h
	${libft_SRC_DIR}/hash/hash.c
	${libft_SRC_DIR}/hash/hash_2.c
	${libft_SRC_DIR}/int/len.c
	${libft_SRC_DIR}/int/str.c
	${libft_SRC_DIR}/io/fmt
	${libft_SRC_DIR}/io/fmt/eval.c
	${libft_SRC_DIR}/io/fmt/fmtd.c
	${libft_SRC_DIR}/io/fmt/fmtm.c
	${libft_SRC_DIR}/io/fmt/fmtpct.c
	${libft_SRC_DIR}/io/fmt/fmts.c
	${libft_SRC_DIR}/io/fmt/fmtxp.c
	${libft_SRC_DIR}/io/fmt/internal.h
	${libft_SRC_DIR}/io/fmt/parse.c
	${libft_SRC_DIR}/io/fmt/type.c
	${libft_SRC_DIR}/io/asprintf.c
	${libft_SRC_DIR}/io/dprintf.c
	${libft_SRC_DIR}/io/fcntl.c
	${libft_SRC_DIR}/io/fflush.c
	${libft_SRC_DIR}/io/fmt.h
	${libft_SRC_DIR}/io/fopen.c
	${libft_SRC_DIR}/io/fprintf.c
	${libft_SRC_DIR}/io/fputc.c
	${libft_SRC_DIR}/io/fputs.c
	${libft_SRC_DIR}/io/fwrite.c
	${libft_SRC_DIR}/io/ifs.c
	${libft_SRC_DIR}/io/ifs_2.c
	${libft_SRC_DIR}/io/internal.h
	${libft_SRC_DIR}/io/printf.c
	${libft_SRC_DIR}/io/snprintf.c
	${libft_SRC_DIR}/io/sprintf.c
	${libft_SRC_DIR}/io/stderr.c
	${libft_SRC_DIR}/io/stdin.c
	${libft_SRC_DIR}/io/stdio.c
	${libft_SRC_DIR}/io/stdout.c
	${libft_SRC_DIR}/io/vasprintf.c
	${libft_SRC_DIR}/io/vdprintf.c
	${libft_SRC_DIR}/io/vfprintf.c
	${libft_SRC_DIR}/io/vprintf.c
	${libft_SRC_DIR}/io/vsnprintf.c
	${libft_SRC_DIR}/io/vsnprintf.h
	${libft_SRC_DIR}/io/vsprintf.c
	${libft_SRC_DIR}/lib/atoi.c
	${libft_SRC_DIR}/lib/clean.c
	${libft_SRC_DIR}/lib/dtor.c
	${libft_SRC_DIR}/lib/error.c
	${libft_SRC_DIR}/lib/getenv.c
	${libft_SRC_DIR}/lib/itoa.c
	${libft_SRC_DIR}/lib/join.c
	${libft_SRC_DIR}/lib/wctomb.c
	${libft_SRC_DIR}/math/eq.c
	${libft_SRC_DIR}/math/eq_2.c
	${libft_SRC_DIR}/math/imax.c
	${libft_SRC_DIR}/math/imin.c
	${libft_SRC_DIR}/math/pow.c
	${libft_SRC_DIR}/math/pow2_next.c
	${libft_SRC_DIR}/math/umax.c
	${libft_SRC_DIR}/math/umin.c
	${libft_SRC_DIR}/mem/alloc.c
	${libft_SRC_DIR}/sort/ft_shellsort.c
	${libft_SRC_DIR}/str/bzero.c
	${libft_SRC_DIR}/str/memccpy.c
	${libft_SRC_DIR}/str/memchr.c
	${libft_SRC_DIR}/str/memcmp.c
	${libft_SRC_DIR}/str/memcpy.c
	${libft_SRC_DIR}/str/memdup.c
	${libft_SRC_DIR}/str/memmove.c
	${libft_SRC_DIR}/str/mempcpy.c
	${libft_SRC_DIR}/str/memrcpy.c
	${libft_SRC_DIR}/str/memset.c
	${libft_SRC_DIR}/str/stpcpy.c
	${libft_SRC_DIR}/str/strbstr.c
	${libft_SRC_DIR}/str/strcat.c
	${libft_SRC_DIR}/str/strchr.c
	${libft_SRC_DIR}/str/strcmp.c
	${libft_SRC_DIR}/str/strcpy.c
	${libft_SRC_DIR}/str/strcspn.c
	${libft_SRC_DIR}/str/strdup.c
	${libft_SRC_DIR}/str/strestr.c
	${libft_SRC_DIR}/str/stris.c
	${libft_SRC_DIR}/str/strlcat.c
	${libft_SRC_DIR}/str/strlcpy.c
	${libft_SRC_DIR}/str/strlen.c
	${libft_SRC_DIR}/str/strmchr.c
	${libft_SRC_DIR}/str/strncat.c
	${libft_SRC_DIR}/str/strnchr.c
	${libft_SRC_DIR}/str/strncmp.c
	${libft_SRC_DIR}/str/strncpy.c
	${libft_SRC_DIR}/str/strndup.c
	${libft_SRC_DIR}/str/strnlen.c
	${libft_SRC_DIR}/str/strnstr.c
	${libft_SRC_DIR}/str/strrchr.c
	${libft_SRC_DIR}/str/strscpy.c
	${libft_SRC_DIR}/str/strspn.c
	${libft_SRC_DIR}/str/strstr.c
	${libft_SRC_DIR}/getopt.c
	${libft_SRC_DIR}/gnl.c)
file(GLOB_RECURSE libft_HDRS ${libft_HDRS} ${libft_INC_DIR}/libft/*.h)
set(libft_HDR ${libft_INC_DIR}/libft.h)

add_library(ft ${libft_SRCS} ${libft_HDRS} ${libft_HDR})
target_include_directories(ft PUBLIC ${libft_INC_DIR})
target_compile_options(ft PUBLIC -Wall -Werror -Wextra -ansi)

set_target_properties(ft PROPERTIES OUTPUT_NAME "ft")
set_target_properties(ft PROPERTIES OUTPUT_NAME_DEBUG "ft.dev")
set_target_properties(ft PROPERTIES OUTPUT_NAME_SAN "ft.san")
set_target_properties(ft PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")
if (CMAKE_C_FLAGS_RELEASE MATCHES "-O3")
	string(REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif ()
if (CMAKE_BUILD_TYPE MATCHES San)
	set_target_properties(ft PROPERTIES COMPILE_FLAGS "-fsanitize=address")
	set_target_properties(ft PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()

install(FILES ${libft_HDRS} DESTINATION include/libft)
install(FILES ${libft_HDR} DESTINATION include)