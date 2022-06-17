# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_unix.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 14:57:47 by mialbert          #+#    #+#              #
#    Updated: 2022/06/17 22:06:28 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS 		:= $(shell uname -s)
ARCH 	:= $(shell uname -m)
SUBM_STATE := $(shell find libs/libft -type f)

NL		:= \n
Q		:= "
NC		:= \033[0m
RED 	:= \033[1;31m
GREEN 	:= \033[1;32m
BLUE 	:= \033[1;34m
PURPLE	:= \033[35;1m

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
