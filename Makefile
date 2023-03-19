# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 14:49:13 by fsemke            #+#    #+#              #
#    Updated: 2023/03/19 17:39:44 by cudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS := -L ./mlx_linux -lmlx -lXext  -lm -I./mlx_linux -L/usr/lib -lX11
	MLX_DIR = mlx_linux
	MLX = mlx_linux/libmlx.a
endif
ifeq ($(OS), Darwin)
	LIBS := -L ./mlx_darwin -lmlx -framework OpenGL -framework Appkit
	MLX_DIR = mlx_darwin
	MLX = mlx_darwin/libmlx.a
endif


NAME = cub3d

SRCS =	src/cub3d.c \
		src/cleanup.c \
		src/check_map.c \
		src/error.c \
		src/ft_split_custom.c \
		src/ft_utils.c \
		src/parsing.c \
		src/read_map.c \
		src/set_map_info.c  \
		src/ft_app_close.c \
		src/ft_img_create_color_img.c \
		src/ft_app_var_init.c \
		src/ft_app_display_map.c \
		src/ft_player_init.c 

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

CC = gcc -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	make -C libft re
	make -C $(MLX_DIR) re
	$(CC) $(SRCS) $(LIBFT) $(LIBS) $(MLX) -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -rf $(OBJS)
	cd libft && make clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C mlx_darwin clean
	make -C mlx_linux clean

re: fclean all

.PHONY: all clean fclean re
