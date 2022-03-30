# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 00:41:49 by mialbert          #+#    #+#              #
#    Updated: 2022/03/30 00:41:52 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
CFLAGS = -Wall -Werror -Wextra
NAME = so_long.a
SRCS = game.c input_handler.c 
OBJS = $(SRCS.c=.o)

all : $(NAME)

# %.o : %.c 
# 	$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	make -C libft/srcs
	$(CC) $(CFLAGS) -c $(SRCS) -Llibft -o $(OBJS)

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re