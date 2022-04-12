# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/04/12 20:13:52 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -g
NAME = so_long
SRCS = ./srcs/input_handler.c ./srcs/free.c ./libs/libft/srcs/*.c ./srcs/error_cases.c  ./srcs/main.c ./srcs/graphics.c ./srcs/logic.c

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