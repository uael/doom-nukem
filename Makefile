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
PROJECT_DIR = $(shell pwd)

CMAKE ?= $(shell (command -v cmake3 || echo cmake))
CMAKE_BUILD_TYPE ?= Debug
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)
BUILD_DIR = build/$(CMAKE_BUILD_TYPE)

all: $(BUILD_DIR)
	@$(CMAKE) --build $(BUILD_DIR) -- -j4

%: $(BUILD_DIR)
	@$(CMAKE) --build $(BUILD_DIR) --target $@ -- -j4

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS) $(PROJECT_DIR)

clean:
	@[ -d $(BUILD_DIR)/CMakeFiles ] && \
		find $(BUILD_DIR)/CMakeFiles -name "*.[oa]" -delete

fclean:
	@[ -d $(BUILD_DIR) ] && \
		find $(BUILD_DIR) -name "*.[oa]" -delete

re: fclean all

.PHONY: clean depend install $(PROJECT) config fclean re
