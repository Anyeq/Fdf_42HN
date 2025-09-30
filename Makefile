# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/19 13:48:49 by asando            #+#    #+#              #
#    Updated: 2025/09/30 10:53:52 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# main flag
CC ?= cc
DEBUG ?= 0
BONUS ?= 0
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -Ofast

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
MLX42_LIBS := -ldl -lglfw -pthread -lm

# fdf src files
SRC_DIR := src
SRC_GRAPH_DIR := $(SRC_DIR)/graphic_src
SRCS := fdf.c parse_file.c parse_file_utils.c error_management.c fdf_utils.c \
		graphic_execution.c graphic_execution_function.c \
		graphic_execution_utils.c

# fdf obj files
OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME := fdf

all: submodules $(NAME)
	@echo "Execution file is created"

#build execution file link all obj needed
$(NAME): libmlx $(LIBFT) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LIBFT) $(MLX42_LIB) $(MLX42_LIBS)

#build mlx42 and compile mlx42
libmlx: $(MLX42_LIB)

$(MLX42_LIB):
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	@cmake --build $(MLX42_DIR)/build -j4
	@echo "libmlx42.a is compiled"

#compile libft
$(LIBFT):
	@$(MAKE) --no-print-directory bonus -C $(LIBFT_DIR)
	@echo "libft.a is compiled"

#compile src to obj
vpath %.c $(SRC_DIR)
vpath %.c $(SRC_GRAPH_DIR)
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(ALL_HEADER) -c $< -o $@

$(OBJ_DIR):
	@echo "Creating Obj files folder..."
	@mkdir -p $(OBJ_DIR)
	@echo "Obj files folder is created"

submodules:
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ] || \
		[ ! -f "$(MLX42_DIR)/CMakeLists.txt" ]; then \
		echo "Initializing Submodules..."; \
		git submodule update --init --recursive; \
	else \
		echo "Submodules are already initialized."; \
	fi

setup: submodules libmlx $(LIBFT)
	@echo "Setting up Library..."

clean:
	@echo "Deleting Obj files..."
	@rm -rf $(OBJ_DIR)
	@echo "Obj files have been deleted"
	@echo "Deleting libft obj files..."
	@rm -rf $(LIBFT_DIR)/obj
	@echo "libft obj files deleted"

fclean: clean
	@echo "Deleting fdf execution file..."
	@rm -rf $(NAME)
	@echo "Fdf execution file has been deleted"
	@echo "Deleting libft.a file..."
	@rm -rf $(LIBFT)
	@echo "libft.a file has been deleted"
	@echo "Deleting libftprintf.a file..."
	@rm -rf $(LIBFT_DIR)/libftprintf.a
	@echo "libftprintf.a file has been deleted"
	@echo "Deleting libmlx_Linux.a file..."
	@rm -rf $(MLX42_DIR)/build
	@echo "MLX42/build folder has been deleted"

re:
	@$(MAKE) --no-print-directory flclean
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re setup libmlx submodules
