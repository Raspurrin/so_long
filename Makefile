# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/04/25 22:24:15 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -g
NAME = so_long
SRCS = ./srcs/input_handler.c \
		./libs/libft/srcs/*.c \
		./srcs/error_cases.c  \
		./srcs/main.c \
		./srcs/graphics.c \
		./srcs/utils.c \
		./srcs/images.c \
		./srcs/enemy.c \
		./srcs/collectible_instance.c \
		./srcs/read_map.c \
		./srcs/more_hooks.c \
		./srcs/other_displays.c

all : $(NAME)

$(NAME) : $(SRCS)
	$(MAKE) -C ./libs/libft/srcs
	$(MAKE) -C ./libs/MLX42
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX42/include/MLX42 \
	-framework Cocoa -framework OpenGL, -framework IOKit $(SRCS) ./libs/MLX42/libmlx42.a \
	 ./libs/libft/srcs/libft.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -fsanitize=address -o $(NAME)

# -fsanitize=address
# ./libs/MLX42/lib-x86_64/libglfw3.a
clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re