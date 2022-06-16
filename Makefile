# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 04:40:17 by mialbert          #+#    #+#              #
#    Updated: 2022/06/16 17:43:00 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS 	:= -Wall -Werror -Wextra
NAME 	:= so_long
LIBFT	:= ./libs/libft/srcs/
LIBMLX 	:= ./libs/MLX/
HEADERS := -I includes -I libs/libft/srcs -I libs/MLX/include 
DEBUG 	:= -fsanitize=address

BONUS 	:= ./libs/libft/srcs/*.c \
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
		  ./bonus/map_parsing/obstacle.c \
		  ./bonus/player/gravity_jump.c \
		  ./bonus/player/movement.c \
		  ./bonus/utils.c \
		  ./bonus/main.c \
		  ./bonus/collectible.c \
		  ./bonus/audio.c

SRCS	:= ./libs/libft/srcs/*.c \
		  ./srcs/graphics/end.c \
		  ./srcs/graphics/graphics.c \
		  ./srcs/graphics/images_to_window.c \
		  ./srcs/graphics/loading_images.c \
		  ./srcs/map_parsing/check_player_amount.c \
		  ./srcs/map_parsing/error_cases.c  \
  		  ./srcs/map_parsing/input_handler.c \
		  ./srcs/map_parsing/read_map.c \
		  ./srcs/map_parsing/obstacle.c \
		  ./srcs/player/gravity_jump.c \
		  ./srcs/player/movement.c \
		  ./srcs/utils.c \
		  ./srcs/main.c \
		  ./srcs/collectible.c

ifeq ($(OS), Windows_NT)
	include Makefile_windows.mk 
else 
	include Makefile_unix.mk
endif

# to automatically initialize the submodules for people who cannot read READMEs
ifeq ($(SUBM_STATE),)
SUBM_FLAG	= submodule
else 
SUBM_FLAG	= 
endif

all : $(SUBM_FLAG) $(OBJS) libft libmlx compile

submodule: 
	git submodule init 
	git submodule update

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	@echo ${NL}${BLUE}======== libft ========${NC}
	@$(MAKE) -C $(LIBFT)

libmlx:
	@echo ${NL}${BLUE}======== MLX42 ========${NC}
	@$(MAKE) -C $(LIBMLX)

compile:
	@echo ${NL}${PURPLE}So_long compiling!${NC}
	$(CC) $(CFLAGS) -g  $(HEADERS) $(LIBS) $(SRCS) $(LIBMLX)libmlx42.a $(LIBFT)libft.a  $(DEBUG) -o $(NAME)

bonus: 
	@echo "${NL}${PURPLE}So_long + bonus compiling!${NC}"
	$(CC) $(CFLAGS) -g  $(HEADERS) $(LIBS) $(BONUS) $(LIBMLX)libmlx42.a $(LIBFT)libft.a $(DEBUG) -o $(NAME)

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

.PHONY: all, libft, libmlx, compile, install on linux, xpm42, clean, fclean, re, bonus
