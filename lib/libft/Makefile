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

BUILD_TYPE ?= Release
BUILD_DIR = build/$(BUILD_TYPE)
BUILD_PROJ_DIR = $(BUILD_DIR)/CMakeFiles

CMAKE ?= cmake
CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
CMAKE_G_FLAGS ?= -j8

.DEFAULT_GOAL := all
.SILENT:
.PHONY: clean config fclean install re

$(BUILD_DIR) config:
	mkdir -p $(BUILD_DIR); cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS) $(CURDIR)

clean:
	[ -d $(BUILD_PROJ_DIR) ] && find $(BUILD_PROJ_DIR) -name "*.o" -delete

fclean:
	[ -d $(BUILD_DIR) ] && find $(BUILD_DIR) -name "*.o" -delete

mrproper:
	rm -rf $(BUILD_DIR)

re: fclean all

%: $(BUILD_DIR)
	$(CMAKE) --build $(BUILD_DIR) --target $@ -- $(CMAKE_G_FLAGS)
