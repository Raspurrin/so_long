# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_windows.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 15:07:19 by mialbert          #+#    #+#              #
#    Updated: 2022/06/17 23:41:56 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SUBM_STATE 	:= $(shell dir "libs\libft")
CC			:= gcc



SRCS		:= $(wildcard $(SRCDIR)\*.c) \
			   $(wildcard $(SRCDIR)\*\*.c) \
			   $(wildcard $(LIBFT)*.c)

BONUS		:= $(wildcard $(BONUSDIR)\*.c) \
			   $(wildcard $(BONUSDIR)\*\*.c) \
			   $(wildcard $(LIBFT)*.c)

SRCS		:= $(subst /,\,$(SRCS))
BONUS		:= $(subst /,\,$(BONUS))
LIBFT		:= $(subst /,\,$(LIBFT))
LIBMLX		:= $(subst /,\,$(LIBMLX))
HEADERS		:= $(subst /,\,$(HEADERS))
BONUS		:= $(subst /,\,$(BONUS))
	
LIBS		:= -lglfw3 -lopengl32 -lgdi32
	
NL			:= 
NC			:= [0m
RED 		:= [91m
GREEN 		:= [92m
BLUE 		:= [96m
PURPLE		:= [95m