# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/19 13:48:49 by asando            #+#    #+#              #
#    Updated: 2025/09/23 11:11:12 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= cc
DEBUG ?= 0
BONUS ?= 0

CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -0fast

MLX42_DIR := ./lib/MLX42
LIBFT_DIR := ./lib/libft

HEADER := include
LIBFT_HEADER := $(LIBFT_DIR)/includes
MLX42_HEADER := $(MLX42_DIR)/include
ALL_HEADER := -I$(HEADER) -I$(LIBFT_HEADER) -I$(MLX42_HEADER)

SRC_DIR := src
SRCS := fdf.c

OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT := $(LIBFT_DIR)/libft.a
MLX42_LIB := $(MLX42_DIR)/build/libmlx42.a
MLX42_LIBS := -ldl -lglfw -lpthread -lm

NAME := fdf

all: $(NAME)

#build execution file link all obj needed
$(NAME): libmlx $(LIBFT) $(OBJS)
	@$(CC) -o $@ $^ $(MLX42_LIB) $(MLX42_LIBS)

#build mlx42 and compile mlx42
libmlx: $(MLX42_LIB)
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

#compile libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

#compile src to obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(ALL_HEADER) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
