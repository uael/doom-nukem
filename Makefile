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

.DEFAULT_GOAL := doom-nukem

# ------------------------------------------------------------------------------
# Configuration
# ------------------------------------------------------------------------------

MAKE_DEPS = Makefile

CC=gcc
LD=gcc

ifneq ($(DEBUG),)
  CONFIG = debug
  CFLAGS += -g3 -O0
  TARGET_SUFFIX = -debug
  ifneq ($(ASAN),)
  	CFLAGS += -fsanitize=address
  endif
else
  CONFIG = release
  CFLAGS += -O3 -Wall -Werror -Wextra
endif

BUILD_DIR = build
BUILD_PATH := $(BUILD_DIR)/$(CONFIG)

# ------------------------------------------------------------------------------
# libft
# ------------------------------------------------------------------------------

LIBFT_LIB=libft/libft.a

$(LIBFT_LIB):
	@$(MAKE) -C $(dir $@)

MAKE_DEPS += $(LIBFT_LIB)
CFLAGS += -Ilibft/include
LDFLAGS += -Llibft -lft -lm

# ------------------------------------------------------------------------------
# sdl2 & sdl2_image
# ------------------------------------------------------------------------------

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  CFLAGS += `pkg-config --cflags sdl2 SDL2_image`
  LDFLAGS += `pkg-config --libs sdl2 SDL2_image`
endif
ifeq ($(UNAME_S),Darwin)
  BREW=$(HOME)/.brew/bin/brew
  SDL2_LIB=$(HOME)/.brew/lib/libSDL2.a
  SDL2_IMAGE_LIB=$(HOME)/.brew/lib/libSDL2_image.a

  $(BREW):
	@./scripts/fixbrew.sh

  $(SDL2_LIB):
	@$(BREW) install sdl2 || true

  $(SDL2_IMAGE_LIB):
	@$(BREW) install sdl2_image || true

  MAKE_DEPS += $(BREW) $(SDL2_LIB) $(SDL2_IMAGE_LIB)
  CFLAGS += -I$(HOME)/.brew/include/
  LDFLAGS += -L$(HOME)/.brew/lib/ -lSDL2 -lSDL2_image
endif

# ------------------------------------------------------------------------------
# Sources & Target
# ------------------------------------------------------------------------------

TARGET = doom-nukem

INCLUDE = include

include src/makefile.mk
MAKE_DEPS += src/makefile.mk

TARGET_BIN := $(TARGET)$(TARGET_SUFFIX)
all: $(TARGET_BIN)

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

$(TARGET_BIN): $(addprefix $(BUILD_PATH)/,$(SRC:.c=.o))
	@echo "  LD      $(notdir $@)"
	$(V)$(LD) $^ $(LDFLAGS) $(addprefix -l,$(LDLIBS)) -o $@

clean:
	@$(RM) -rf $(BUILD_DIR)

fclean: clean
	@$(RM) -f $(TARGET_BIN)

re: fclean all