# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/05/13 23:28:29 by mialbert         ###   ########.fr        #
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
		./bonus/loading_images.c \
		./bonus/enemy_interaction.c \
		./bonus/enemy_spawn.c \
		./bonus/collectible.c \
		./bonus/read_map.c \
		./bonus/display.c \
		./bonus/gravity_jump.c \
		./bonus/movement.c \
		./bonus/check_player_amount.c \
		./bonus/images_to_window.c \
		./bonus/animation.c

all : $(NAME)
OS := $(shell uname -s)
ARCH := $(shell uname -m)

ifeq ($(ARCH), x86_64)
GLFW := libs/MLX/lib/lib-x86_64/libglfw3.a
else ifeq ($(ARCH), arm)
GLFW := libs/MLX/lib/lib-arm64/libglfw3.a
else 
GLFW := libs/MLX/lib/lib-universal/libglfw3.a
endif

$(NAME) : $(BONUS)
	$(MAKE) -C ./libs/libft/srcs
	$(MAKE) -C ./libs/MLX
	$(MAKE) $(OS)

Darwin:
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX/include \
	-framework Cocoa -framework OpenGL, -framework IOKit $(BONUS) ./libs/MLX/libmlx42.a \
	 ./libs/libft/srcs/libft.a $(GLFW) -L "/Users/$(USER)/.brew/opt/glfw/lib/" -fsanitize=address -o $(NAME)

Linux:   
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX/include \
	 $(BONUS) ./libs/MLX/libmlx42.a -ldl -lglfw \
	 ./libs/libft/srcs/libft.a -L "/Users/$(USER)/.brew/opt/glfw/lib/" -fsanitize=address -o $(NAME)

install linux: 
	sudo apt update 
	sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev

# -fsanitize=address
# ./libs/MLX42/lib-x86_64/libglfw3.a
clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re