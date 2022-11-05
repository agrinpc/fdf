# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 18:42:39 by miahmadi          #+#    #+#              #
#    Updated: 2022/10/25 20:21:41 by miahmadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a
PROG = fdf

LIBFT = ./libft
MLX = ./mlx
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Imlx
AR = ar rcs
RM = rm -f

FILES = main \

FILES_B = 	ft_lstnew \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))


%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(PROG)

$(PROG): $(NAME)
	$(CC) $(NAME) -Lmlx -lmlx -framework OpenGL -framework AppKit  -o $(PROG) $(CFLAGS) -g

$(NAME): premake
	$(AR) $@ $(OBJS)

bonus: $(OBJS_B)
	$(AR) $(NAME) $^

premake: mlx
	@make -C $(LIBFT)
	@cp $(LIBFT)/libft.a .
	@mv libft.a $(NAME)
	
mlx: $(OBJS)
	@make -C $(MLX)
	@cp $(MLX)/libmlx.dylib .
	@mv libmlx.dylib libmlx.dylib

clean:
	$(RM) $(OBJS) $(OBJS_B)
	@cd $(LIBFT) && $(MAKE) clean

fclean: clean
	$(RM) $(NAME) $(PROG)
	@cd $(LIBFT) && $(MAKE) fclean

re: clean all

.PHONY: bonus all clean fclean re $(PROG) $(NAME)
