# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#              #
#    Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = ft

THIS_DIR = $(shell pwd)
filter-false = $(strip $(filter-out 0 off OFF false FALSE,$1))
filter-true = $(strip $(filter-out 1 on ON true TRUE,$1))

CMAKE_PRG ?= $(shell (command -v cmake3 || echo cmake))
CMAKE_BUILD_TYPE ?= Debug

CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

BUILD_TYPE ?= Unix Makefiles

ifeq (,$(BUILD_TOOL))
  ifeq (Ninja,$(BUILD_TYPE))
    ifneq ($(shell $(CMAKE_PRG) --help 2>/dev/null | grep Ninja),)
      BUILD_TOOL := ninja
    else
      # User's version of CMake doesn't support Ninja
      BUILD_TOOL = $(MAKE)
      BUILD_TYPE := Unix Makefiles
    endif
  else
    BUILD_TOOL = $(MAKE)
  endif
endif

ifneq ($(VERBOSE),)
  # Only need to handle Ninja here.  Make will inherit the VERBOSE variable.
  ifeq ($(BUILD_TYPE),Ninja)
    VERBOSE_FLAG := -v
  endif
endif

BUILD_CMD = $(BUILD_TOOL) $(VERBOSE_FLAG)

# Extra CMake flags which extend the default set
CMAKE_EXTRA_FLAGS ?=
DEPS_CMAKE_FLAGS ?=
USE_BUNDLED_DEPS ?=

# For use where we want to make sure only a single job is run.  This does issue
# a warning, but we need to keep SCRIPTS argument.
SINGLE_MAKE = export MAKEFLAGS= ; $(MAKE)

all: build/.ran-cmake
	@+$(BUILD_CMD) -C build

%: build/.ran-cmake
	@+$(BUILD_CMD) -C build $@

help: build/.ran-cmake
	@+$(BUILD_CMD) -C build help
	@echo "... libft"
	@echo "... clean"
	@echo "... distclean"
	@echo "... re"
	@echo "... install"

build/.ran-cmake:
	@mkdir -p build
	@cd build && $(CMAKE_PRG) -G '$(BUILD_TYPE)' $(CMAKE_FLAGS) $(CMAKE_EXTRA_FLAGS) $(THIS_DIR)
	@touch $@

config:
	@cd build && $(CMAKE_PRG) -G '$(BUILD_TYPE)' $(CMAKE_FLAGS) $(CMAKE_EXTRA_FLAGS) $(THIS_DIR)

clean:
	@+test -d build && $(BUILD_CMD) -C build clean || true

distclean: clean
	@rm -rf build

re: clean all

libft.a: all

install: | ft
	@+$(BUILD_CMD) -C build install

.PHONY: clean distclean re install
