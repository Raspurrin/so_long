# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/04/29 03:25:33 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -g
NAME = so_long
BONUS =	./libs/libft/srcs/*.c \
  		./bonus/input_handler.c \
		./bonus/error_cases.c  \
		./bonus/main.c \
		./bonus/graphics.c \
		./bonus/utils.c \
		./bonus/images.c \
		./bonus/enemy.c \
		./bonus/collectible.c \
		./bonus/read_map.c \
		./bonus/display.c \
		./bonus/extra_features.c \
		./bonus/movement.c \
		./bonus/check_player_amount.c

SRCS = ./libs/libft/srcs/*.c \
  		./srcs/input_handler.c \
		./srcs/error_cases.c  \
		./srcs/main.c \
		./srcs/graphics.c \
		./srcs/utils.c \
		./srcs/images.c \
		./srcs/collectible.c \
		./srcs/read_map.c \
		./srcs/display.c \
		./srcs/extra_features.c \
		./srcs/movement.c \
		./srcs/check_player_amount.c

all : $(NAME)

$(NAME) : $(SRCS)
	$(MAKE) -C ./libs/libft/srcs
	$(MAKE) -C ./libs/MLX42
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX42/include \
	-framework Cocoa -framework OpenGL, -framework IOKit $(SRCS) ./libs/MLX42/libmlx42.a \
	 ./libs/libft/srcs/libft.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

bonus : $(BONUS)
	$(MAKE) -C ./libs/libft/srcs
	$(MAKE) -C ./libs/MLX42
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX42/include \
	-framework Cocoa -framework OpenGL, -framework IOKit $(BONUS) ./libs/MLX42/libmlx42.a \
	 ./libs/libft/srcs/libft.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

# -fsanitize=address
# ./libs/MLX42/lib-x86_64/libglfw3.a
clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re