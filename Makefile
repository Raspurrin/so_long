# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 04:40:17 by mialbert          #+#    #+#              #
#    Updated: 2022/06/01 17:54:08 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS 	= -Wall -Werror -Wextra -g
NAME 	= so_long
LIBFT	= ./libs/libft/srcs
LIBMLX 	= ./libs/MLX
HEADERS = -I includes -I libs/libft/srcs -I libs/MLX/include -I libs/miniaudio
DEBUG 	= 
# -fsanitizer=address
BONUS 	= ./libs/libft/srcs/*.c \
		  ./bonus/enemy/damage.c \
		  ./bonus/enemy/init.c \
		  ./bonus/enemy/interaction.c \
		  ./bonus/enemy/spawn.c \
		  ./bonus/graphics/animation.c \
		  ./bonus/graphics/display.c \
		  ./bonus/graphics/end.c \
		  ./bonus/graphics/graphics.c \
		  ./bonus/graphics/images_to_window.c \
		  ./bonus/graphics/loading_images.c \
		  ./bonus/map_parsing/check_player_amount.c \
		  ./bonus/map_parsing/error_cases.c  \
  		  ./bonus/map_parsing/input_handler.c \
		  ./bonus/map_parsing/read_map.c \
		  ./bonus/player/gravity_jump.c \
		  ./bonus/player/movement.c \
		  ./bonus/utils.c \
		  ./bonus/main.c \
		  ./bonus/collectible.c 

NC		:= \033[0m
RED 	:= \033[1;31m
GREEN 	:= \033[1;32m
BLUE 	:= \033[1;34m
PURPLE	:= \033[35;1m

OS 		:= $(shell uname -s)
ARCH 	:= $(shell uname -m)

# determining architecture for the Mac
ifeq ($(ARCH), x86_64)
GLFW 	:= libs/MLX/lib/lib-x86_64/libglfw3.a
else ifeq ($(ARCH), arm)
GLFW 	:= libs/MLX/lib/lib-arm64/libglfw3.a
else 
GLFW 	:= libs/MLX/lib/lib-universal/libglfw3.a
endif

# for cross-platform compatibility
ifeq ($(OS), Darwin)
LIBS	:= -framework Cocoa -framework OpenGL, -framework IOKit $(GLFW)
else ifeq ($(OS), Linux)
LIBS	:= -ldl -lglfw
endif

%.o : %.c # IT NOT WORK !!
	@$(CC) $(CFLAGS) $< -o $@

all : $(OBJS) libft libmlx compile 

libft:
	@echo "\n${BLUE}======== libft ========${NC}"
	@$(MAKE) -C $(LIBFT)

libmlx:
	@echo "\n${BLUE}======== MLX42 ========${NC}"
	@$(MAKE) -C $(LIBMLX)

compile:
	@echo "\n${PURPLE}so_long compiling!${NC}"
	@$(CC) $(CFLAGS) -g  $(HEADERS) $(LIBS) $(BONUS) $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a $(DEBUG) -o $(NAME)

# run this to install the required packages for Linux
install on linux:
	@sudo apt update && sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev

# to make the xpm -> xpm42 convertion more easy
xpm42:
	@python3 libs/MLX/tools/xpm3_conv.py textures/$(IMG).xpm

clean:
	@rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: fclean all

.PHONY: all, libft, libmlx, compile, install on linux, xpm42, clean, fclean, re