# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/04/04 21:43:12 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = so_long
SRCS = input_handler.c free.c

all : $(NAME)

$(NAME) :
	$(MAKE) -C libft/srcs
	$(CC) $(CFLAGS) -g $(SRCS) libft/srcs/libft.a -o $(NAME)
#	#./so_long map.ber

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re