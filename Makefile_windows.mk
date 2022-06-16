# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_windows.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 15:07:19 by mialbert          #+#    #+#              #
#    Updated: 2022/06/16 15:07:19 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SUBM_STATE 	:= $(shell dir "libs\libft")
CC			:= gcc

SRCS		:= $(subst /,\,$(SRCS))
LIBFT		:= $(subst /,\,$(LIBFT))
LIBMLX		:= $(subst /,\,$(LIBMLX))
HEADERS		:= $(subst /,\,$(HEADERS))
BONUS		:= $(subst /,\,$(BONUS))
	
LIBS		:= -lglfw3 -lopengl32 -lgdl32 
	
NL			:= 
NC			:= [0m
RED 		:= [91m
GREEN 		:= [92m
BLUE 		:= [96m
PURPLE		:= [95m
