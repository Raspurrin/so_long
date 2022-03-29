CC= gcc
CFLAGS = -Wall -Werror -Wextra
NAME = so_long.a
SRCS = game.c input_handler.c 
OBJS = $(SRCS.c=.o)

all : $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	make -C ./get_next_line/Make
clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY clean fclean re 