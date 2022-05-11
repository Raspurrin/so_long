# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/05/11 23:41:29 by mialbert         ###   ########.fr        #
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

$(NAME) : $(BONUS)
	$(MAKE) -C ./libs/libft/srcs
	$(MAKE) -C ./libs/MLX42
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX42/include \
	-framework Cocoa -framework OpenGL, -framework IOKit $(BONUS) ./libs/MLX42/libmlx42.a \
	 ./libs/libft/srcs/libft.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -fsanitize=leak -o $(NAME)

# -fsanitize=address
# ./libs/MLX42/lib-x86_64/libglfw3.a
clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re