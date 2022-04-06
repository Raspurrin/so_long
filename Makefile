# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/04/06 15:35:12 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = so_long
SRCS = ./srcs/input_handler.c ./srcs/free.c ./libs/libft/srcs/*.c ./srcs/error_cases.c  ./srcs/main.c ./srcs/graphics.c

all : $(NAME)

$(NAME) :
	$(MAKE) -C ./libs/libft/srcs
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX42/include/MLX42 \
	-framework Cocoa -framework OpenGL, -framework IOKit $(SRCS) ./libs/MLX42/libmlx42.a \
	./libs/MLX42/lib-x86_64/libglfw3.a ./libs/libft/srcs/libft.a -o $(NAME)

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re