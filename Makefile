# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025-07-16 18:28:58 by kelevequ          #+#    #+#              #
#    Updated: 2025-07-16 18:28:58 by kelevequ         ###   ########.lu        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/controls/cub3d_controls.c \
		src/controls/cub3d_events.c \
		src/engine/cub3d_engine.c \
		src/engine/cub3d_ray.c \
		src/engine/cub3d_textures.c \
		src/cub3d_init.c \
		src/main.c

OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
HDRS =	cub3d.h \
		cub3d_map.h \
		cub3d_img.h \
		cub3d_point.h \
		cub3d_player.h \
		cub3d_engine.h \
		cub3d_extlibs.h \
		cub3d_controls.h
INCLUDE_PATH = include
INCLUDE = $(addprefix $(INCLUDE_PATH)/, $(HDRS))
NAME = cub3d
RM = rm -rf
CC = cc
FLAGS = -Wall -Wextra -Werror -g
MLX_PATH	= ./src/minilibx-linux
MLX			= $(MLX_PATH)/libmlx.a

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I$(INCLUDE_PATH) -I$(MLX_PATH) -c $< -o $@

$(NAME): $(MLX) $(OBJS) $(OBJS_DIR)
	$(CC) -o $(NAME) $(OBJS) -L$(MLX_PATH) -lmlx -lX11 -lXext -lmlx -lm

$(MLX):
	make -C $(MLX_PATH) all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

all: $(NAME)

re: fclean all

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)
	make -C $(MLX_PATH) clean

.PHONY: all clean fclean re