# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 04:40:17 by mialbert          #+#    #+#              #
#    Updated: 2022/06/24 10:51:20 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS 		:= -Wall -Werror -Wextra
NAME 		:= so_long
LIBFT		:= ./libs/libft/srcs/
LIBMLX 		:= ./libs/MLX/
HEADERS 	:= -I includes -I libs/libft/srcs -I libs/MLX/include 
SRCDIR		:= ./srcs/
BONUSDIR 	:= ./bonus/
UNIXDIR		:= ./bonus/unix/

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
	@echo ${Q}${NL}${BLUE}======== libft ========${NC}${Q}
	@$(MAKE) -C $(LIBFT)

libmlx:
	@echo ${Q}${NL}${BLUE}======== MLX42 ========${NC}${Q}
	@$(MAKE) -C $(LIBMLX)

compile:
	@echo ${Q}${NL}${PURPLE}So_long compiling!${NC}${Q}
	$(CC) $(CFLAGS) -g $(HEADERS) $(SRCS) $(LIBMLX)libmlx42.a $(LIBFT)libft.a $(LIBS) $(DEBUG) -o $(NAME)

bonus: $(SUBM_FLAG) libft libmlx
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
