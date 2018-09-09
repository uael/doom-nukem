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

.DEFAULT_GOAL := libft.a

# ------------------------------------------------------------------------------
# Configuration
# ------------------------------------------------------------------------------

MAKE_DEPS = Makefile

CC=gcc
LD=gcc

ifneq ($(DEBUG),)
  CONFIG = debug
  CFLAGS += -g -O0
  TARGET_SUFFIX = -debug
else
  CONFIG = release
  CFLAGS += -O3 -Wall -Werror -Wextra
endif

BUILD_DIR = build
BUILD_PATH := $(BUILD_DIR)/$(CONFIG)

# ------------------------------------------------------------------------------
# Sources & Target
# ------------------------------------------------------------------------------

TARGET = libft

INCLUDE = include

include src/makefile.mk
MAKE_DEPS += src/makefile.mk

TARGET_LIB := $(TARGET)$(TARGET_SUFFIX).a
all: $(TARGET_LIB)

# ------------------------------------------------------------------------------
# Rules
# ------------------------------------------------------------------------------

V ?= @

-include $(addprefix $(BUILD_PATH)/,$(SRC:.c=.d))

$(BUILD_PATH)/%.o: %.c $(MAKE_DEPS)
	@echo "  CC      $(notdir $<)"
	@mkdir -p $(dir $@)
	$(V)$(CC) $< -c $(CFLAGS) $(addprefix -I,$(INCLUDE)) \
		$(addprefix -D,$(DEFINE)) -MMD -MF $(@:.o=.d) -o $@

$(TARGET_LIB): $(addprefix $(BUILD_PATH)/,$(SRC:.c=.o))
	@echo "  LD      $(notdir $@)"
	$(V)ar -rc $(TARGET).a $^
	$(V)ranlib $(TARGET).a

clean:
	@$(RM) -rf $(BUILD_DIR)

fclean: clean
	@$(RM) -f $(TARGET_BIN)

re: fclean all
