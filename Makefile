# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/04/05 22:39:54 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = so_long
SRCS = ./srcs/input_handler.c ./srcs/free.c ./libs/libft/srcs/*.c ./srcs/main.c ./srcs/error_cases.c

all : $(NAME)

$(NAME) :
	$(MAKE) -C ./libs/libft/srcs
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs $(SRCS) ./libs/libft/srcs/libft.a -o $(NAME)
#	#./so_long map.ber

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re