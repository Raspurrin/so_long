
CFLAGS = -Wall -Werror -Wextra -g
NAME = so_long
BONUS =	./libs/libft/srcs/*.c \
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

all : $(NAME)
OS := $(shell uname -s)
ARCH := $(shell uname -m)

ifeq ($(ARCH), x86_64)
GLFW := libs/MLX/lib/lib-x86_64/libglfw3.a
else ifeq ($(ARCH), arm)
GLFW := libs/MLX/lib/lib-arm64/libglfw3.a
else 
GLFW := libs/MLX/lib/lib-universal/libglfw3.a
endif

$(NAME) : $(BONUS)
	$(MAKE) -C ./libs/libft/srcs
	$(MAKE) -C ./libs/MLX
	$(MAKE) $(OS)

Darwin:
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX/include \
	-framework Cocoa -framework OpenGL, -framework IOKit $(BONUS) ./libs/MLX/libmlx42.a \
	 ./libs/libft/srcs/libft.a $(GLFW) -fsanitize=address -o $(NAME)

Linux:   
	$(CC) $(CFLAGS) -g -I includes -I libs/libft/srcs -I libs/MLX/include \
	 $(BONUS) ./libs/MLX/libmlx42.a -ldl -lglfw \
	 ./libs/libft/srcs/libft.a -fsanitize=address -o $(NAME)

install linux:
	sudo apt update 
	sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev

xpm42:
	python3 libs/MLX/tools/xpm3_conv.py textures/$(IMG).xpm

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re