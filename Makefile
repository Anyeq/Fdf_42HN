# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/19 13:48:49 by asando            #+#    #+#              #
#    Updated: 2025/09/23 16:10:25 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# main flag
CC ?= cc
DEBUG ?= 0
BONUS ?= 0
CFLAGS := -Wall -Wextra -Werror

# library directory
MINILIB_DIR := ./lib/minilibx-linux
LIBFT_DIR := ./lib/libft

# library Header
HEADER := include
LIBFT_HEADER := $(LIBFT_DIR)/includes
MINILIB_HEADER := $(MINILIB_DIR)
ALL_HEADER := -I$(HEADER) -I$(LIBFT_HEADER) -I$(MINILIB_HEADER)

# library archive files
LIBFT := $(LIBFT_DIR)/libft.a
MINILIB_LIB := $(MINILIB_DIR)/libmlx_Linux.a
#MLX42_LIBS := -ldl -lglfw -lpthread -lm

# fdf src files
SRC_DIR := src
SRCS := fdf.c

# fdf obj files
OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME := fdf

all: submodules $(NAME)
	@echo "Execution file is created"

#build execution file link all obj needed
$(NAME): libmlx $(LIBFT) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LIBFT) $(MINILIB_LIB)

#build mlx42 and compile mlx42
libmlx: $(MINILIB_LIB)

$(MINILIB_LIB):
	@$(MAKE) --no-print-directory -C $(MINILIB_DIR)
	@echo "Minilibx is compiled"

#compile libft
$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

#compile src to obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(ALL_HEADER) -c $< -o $@

$(OBJ_DIR):
	@echo "Creating Obj files folder..."
	@mkdir -p $(OBJ_DIR)
	@echo "Obj files folder is created"

submodules:
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ] || \
		[ ! -f "$(MINILIB_DIR)/Makefile" ]; then \
		echo "Initializing Submodules..."; \
		git submodule update --init --recursive; \
	else \
		echo "Submodules are already initialized."; \
	fi

setup: submodules libmlx $(LIBFT)
	@echo "Setting up Library"

clean:
	@echo "Deleting Obj files..."
	@rm -rf $(OBJ_DIR)
	@echo "Obj files have been deleted"
	@echo "Deleting Library obj files..."
	@rm -rf $(LIBFT_DIR)/obj
	@rm -rf $(MINILIB_DIR)/obj
	@echo "Library obj files have been deleted"

fclean: clean lib_clean
	@echo "Deleting fdf execution file..."
	@rm -rf $(NAME)
	@echo "Fdf execution file has been deleted"
	@echo "Deleting libft.a file..."
	@rm -rf $(LIBFT)
	@echo "libft.a file has been deleted"
	@echo "Deleting libmlx_Linux.a file..."
	@rm -rf $(MINILIB_LIB)
	@echo "libmlx_Linux.a file has been deleted"

re:
	@$(MAKE) --no-print-directory flclean
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re setup libmlx submodules
