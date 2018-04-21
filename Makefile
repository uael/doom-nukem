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

PROJECT = wolf3d

THIS_DIR = $(shell pwd)
filter-false = $(strip $(filter-out 0 off OFF false FALSE,$1))
filter-true = $(strip $(filter-out 1 on ON true TRUE,$1))

CMAKE_PRG ?= $(shell (command -v cmake3 || echo cmake))
CMAKE_BUILD_TYPE ?= Release
ifeq (Release,$(BUILD_TOOL))
  BUILD_DIR = build/rel
else
  ifeq (Debug,$(BUILD_TOOL))
    BUILD_DIR = build/dev
  else
    BUILD_DIR = build/san
  endif
endif

CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)
BUILD_TOOL = $(MAKE)
BUILD_TYPE ?= Unix Makefiles
BUILD_CMD = $(BUILD_TOOL)

# Extra CMake flags which extend the default set
CMAKE_EXTRA_FLAGS ?=
DEPS_CMAKE_FLAGS ?=
USE_BUNDLED_DEPS ?=

# For use where we want to make sure only a single job is run.  This does issue
# a warning, but we need to keep SCRIPTS argument.
SINGLE_MAKE = export MAKEFLAGS= ; $(MAKE)

all: rel

$(PROJECT):$(BUILD_DIR)/.ran-cmake
	@+$(BUILD_CMD) -C $(BUILD_DIR)

rel:
	CMAKE_BUILD_TYPE=Release $(MAKE) $(PROJECT)

dev:
	CMAKE_BUILD_TYPE=Debug $(MAKE) $(PROJECT)

san:
	CMAKE_BUILD_TYPE=San $(MAKE) $(PROJECT)

%: $(BUILD_DIR)/.ran-cmake
	@+$(BUILD_CMD) -C $(BUILD_DIR) $@

help: $(BUILD_DIR)/.ran-cmake
	@+$(BUILD_CMD) -C $(BUILD_DIR) help
	@echo "... clean"
	@echo "... fclean"
	@echo "... re"
	@echo "... install"

$(BUILD_DIR)/.ran-cmake:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE_PRG) -G '$(BUILD_TYPE)' $(CMAKE_FLAGS) $(CMAKE_EXTRA_FLAGS) $(THIS_DIR)
	@touch $@

config:
	@cd $(BUILD_DIR) && $(CMAKE_PRG) -G '$(BUILD_TYPE)' $(CMAKE_FLAGS) $(CMAKE_EXTRA_FLAGS) $(THIS_DIR)

clean:
	@+test -d $(BUILD_DIR) && $(BUILD_CMD) -C $(BUILD_DIR) clean || true

fclean: clean
	@rm -rf $(BUILD_DIR)

re: fclean all

install: $(PROJECT)
	@+$(BUILD_CMD) -C $(BUILD_DIR) install

.PHONY: clean distclean re install
