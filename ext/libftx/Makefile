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

CMAKE ?= cmake
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
MAKE_FLAGS ?= -j8

BUILD_DIR = build/$(BUILD_TYPE)
BUILD_PROJ_DIR = $(BUILD_DIR)/CMakeFiles

.DEFAULT_GOAL := all

$(BUILD_DIR) config:
	@mkdir -p $(BUILD_DIR); cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS) $(CURDIR)

clean:
	@[ -d $(BUILD_PROJ_DIR) ] && find $(BUILD_PROJ_DIR) -name "*.[oa]" -delete

distclean fclean:
	@[ -d $(BUILD_DIR) ] && find $(BUILD_DIR) -name "*.[oa]" -delete

mrproper:
	@rm -rf $(BUILD_DIR)

re: fclean all

%: $(BUILD_DIR)
	@$(CMAKE) --build $(BUILD_DIR) --target $@ -- $(MAKE_FLAGS)

.PHONY: clean depend install config distclean fclean re
