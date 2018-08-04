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

NAME = wolf3d

.SILENT:
.DEFAULT_GOAL := $(NAME)
.PHONY: clean conf dev fclean install re reconf san

BUILD_TYPE ?= Release
BUILD_DIR ?= build/$(BUILD_TYPE)
BUILD_PROJ_DIR = $(BUILD_DIR)/CMakeFiles

CMAKE ?= cmake
CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
CMAKE_G_FLAGS ?= -j8

ifeq (1,$(VERBOSE))
  CMAKE_FLAGS += -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
  CMAKE_G_FLAGS += VERBOSE=1
endif

$(BUILD_DIR) conf:
	mkdir -p $(BUILD_DIR); cd $(BUILD_DIR); $(CMAKE) $(CMAKE_FLAGS) $(CURDIR)

reconf: fclean conf

dev:
	$(MAKE) BUILD_TYPE=Debug

san:
	$(MAKE) BUILD_TYPE=San

clean:
	$(RM) -rf $(BUILD_PROJ_DIR)

fclean: clean
	$(RM) -f wolf3d*

mrproper: fclean
	$(RM) -rf build

re: fclean all

re_san:
	$(MAKE) BUILD_TYPE=San re

re_dev:
	$(MAKE) BUILD_TYPE=Debug re

$(NAME) all: $(BUILD_DIR)
	$(CMAKE) --build $(BUILD_DIR) --target $@ -- $(CMAKE_G_FLAGS)
