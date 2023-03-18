# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 11:34:52 by fsemke            #+#    #+#              #
#    Updated: 2023/03/14 14:28:34 by fsemke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libft.a

SRC = 	ft_isalpha.c	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_strlen.c		\
		ft_memset.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strncmp.c	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_strnstr.c	\
		ft_atoi.c		\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c
		
SRC_B =	ft_lstadd_back.c	\
		ft_lstadd_front.c	\
		ft_lstclear.c		\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstlast.c		\
		ft_lstmap.c			\
		ft_lstnew.c			\
		ft_lstsize.c

SRC_PRINTF = ft_printf.c		\
		ft_cases.c \
		ft_helpfunctions.c \
		ft_struct.c \
		ft_hex.c \
		ft_num.c
		
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
OBJ_PRINTF = $(SRC_PRINTF:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME) $(OBJ_PRINTF)

bonus: $(NAME)
	ar rc $(NAME) $(OBJ_B)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC)
	$(CC) $(FLAGS) -c $(addprefix srcs_printf/, $(SRC_PRINTF))
	ar rc $(NAME) $(OBJ) $(OBJ_PRINTF)

clean:
	rm -f $(OBJ) $(OBJ_B) $(OBJ_PRINTF)

fclean: clean
	rm -f $(NAME)

re: fclean all