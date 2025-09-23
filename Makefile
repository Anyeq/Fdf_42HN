# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/19 13:48:49 by asando            #+#    #+#              #
#    Updated: 2025/09/23 12:01:30 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# main flag
CC ?= cc
DEBUG ?= 0
BONUS ?= 0
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -0fast

# library directory
MLX42_DIR := ./lib/MLX42
LIBFT_DIR := ./lib/libft

# library Header
HEADER := include
LIBFT_HEADER := $(LIBFT_DIR)/includes
MLX42_HEADER := $(MLX42_DIR)/include
ALL_HEADER := -I$(HEADER) -I$(LIBFT_HEADER) -I$(MLX42_HEADER)

# library archive files
LIBFT := $(LIBFT_DIR)/libft.a
MLX42_LIB := $(MLX42_DIR)/build/libmlx42.a
MLX42_LIBS := -ldl -lglfw -lpthread -lm

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
	@$(CC) -o $@ $^ $(MLX42_LIB) $(MLX42_LIBS)

#build mlx42 and compile mlx42
libmlx: $(MLX42_LIB)
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

#compile libft
$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

#compile src to obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(ALL_HEADER) -c $< -o $@

$(OBJ_DIR):
	@echo "Creating Obj files folder..."
	@mkdir -p $(OBJ_DIR)

submodules:
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ] 
	|| [ ! -f "$(MLX42_DIR)/CMakeLists.txt" ] then \
		echo "Initializing Submodules..."; \
		git submodule update --init --recursive; \
	else \
		echo "Submodules are already initialized."; \
	fi

setup: submodules libmlx $(LIBFT)
	@echo "Setting up Library"

clean:
	@echo "Deleting Obj files and folder..."
	@rm -rf $(OBJ_DIR)

lib_clean:
	@echo "Deleting Library obj files and folder..."
	@rm -rf $(LIBFT_DIR)/obj
	@rm -rf $(MLX42_DIR)/build

fclean: clean lib_clean
	@echo "Deleting Program file..."
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@echo "Program file is deleted"

re:
	@$(MAKE) --no-print-directory flclean
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re setup
