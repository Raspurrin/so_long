/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/17 03:46:48 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BLOK 32
# define GHOSTCOUNT 1
# define LIVES 7
# define ACCEL 1
# define ACCEL_MOD 1.3
# define JUMP_CAP 100
# define FATASS 10
# define FATBOO 10
# define SPEED 18
# define IMMORTAL 0
# define KILL 1
# define GRAV 1
# define BUFFERSIZE 30

typedef enum move
{
	X,
	Y,
	XY
}	t_move;

typedef enum mlx_images
{
	STRLIFE,
	STRMOVE,
	PICKUP,
	CHAR,
	DOOR,
	TILE,
	WALL,
	SLIME,
	BG,
	BRICK,
	GHOST,
	SCREEN,
	GREY,
	RED,
	PINK,
	IMG_COUNT,
}	t_images;

typedef enum string
{
	LIFE,
	MOVE,
	FRAME,
	TEST,
	STR_COUNT,
}	t_string;

typedef struct line
{
	size_t	count;
	size_t	size;
}	t_line;

typedef struct animate
{
	uint32_t	length;
	uint32_t	start;
	uint32_t	xy[XY];
}	t_animate;

typedef struct enemy
{
	size_t				current_time;
	size_t				max;
	size_t				time;
	int32_t				x[GHOSTCOUNT + 1];
	int32_t				y[GHOSTCOUNT + 1];
	size_t				excep_count;
	size_t				excep[GHOSTCOUNT];
	size_t				move[GHOSTCOUNT];
	mlx_image_t			*img[GHOSTCOUNT];
	bool				time_lock;
}	t_enemy;

typedef struct image_data
{
	t_animate			animate;
	float				accel;
	char				*bigass;
	uint32_t			char_start;
	size_t				collect;
	char				*combstr[STR_COUNT];
	int32_t				count[STR_COUNT];
	bool				counter_lock;
	t_enemy				enemy;
	bool				fly;
	mlx_texture_t		*ghost;
	mlx_texture_t		*ghost_r;
	int32_t				height;
	mlx_image_t			*img[IMG_COUNT];
	mlx_key_data_t		*keydata;
	bool				jump_lock;
	t_line				line;
	char				**map;
	mlx_t				*mlx;
	size_t				old_x;
	size_t				old_y;
	int32_t				pid;
	uint8_t				*pixel;
	uint8_t				startingpoint;
	char				*str[STR_COUNT];
	size_t				tile_move;
	int32_t				width;
	xpm_t				*xpm[IMG_COUNT];
	uint32_t			xy[2];			
}	t_imgdata;

typedef struct error_cases
{
	bool	error;
	bool	file_name;
	bool	walls;
	bool	no_cpe;
	bool	different_input;
	bool	not_rectangular;
	bool	morecharacters;
	bool	enemyoverflow;
	bool	enemyunderflow;
}	t_error;

void	animate_char(t_imgdata *data, t_animate *animate, size_t x, size_t y);
void	animate_ghosts(t_imgdata *data, mlx_texture_t *ghost, \
								t_enemy *enemy, size_t i);
bool	check_ext(char *file_name, char *ext);
void	check_player_amount(t_error *errors, t_imgdata *data);
void	collect(t_imgdata *data, size_t x, size_t y);
void	colour_screen(t_imgdata *data, int32_t macro, int32_t colour);
void	display_message(t_imgdata *data, bool death, float x_mod, float y_mod);
void	display_string(t_imgdata *data, int32_t str_img, size_t x, char *str);
void	end(mlx_key_data_t keydata, void *data);
void	end_message(t_imgdata *data);
void	enemies(t_imgdata *data, t_enemy *enemy, size_t x, size_t y);
bool	enemy_to_window(t_imgdata *data, t_enemy *enemy);
void	error_output(t_error *errors, t_line *line);
void	error_close_window(t_imgdata *data, char *str);
int32_t	find_c_instance(t_imgdata *data, size_t index);
void	free_2d(char **map);
bool	free_array(mlx_image_t **arr, char *str, t_imgdata *data);
void	free_close_window(t_imgdata *data, void *var, char *str);
void	gravity(t_imgdata *data, size_t x, size_t y);
size_t	getncount(char *str, uint8_t chr);
size_t	getncount(char *str, uint8_t chr);
void	get_ghost_spawn(t_imgdata *data);
int32_t	graphics(t_imgdata *data, t_line *line);
bool	images_to_window(t_imgdata *data, size_t i);
char	**input_handler(int32_t fd, t_imgdata *data, \
						t_line *line, t_enemy *enemy);
bool	loading_images(t_imgdata *data, xpm_t **xpm);
void	movement(t_imgdata *data, size_t x, size_t y);
void	movecounter(t_imgdata *data, t_animate *animate, size_t x, size_t y);
char	*read_file(int32_t fd);
void	terminate(t_imgdata *data);
bool	texture_to_image(t_imgdata *data, xpm_t **xpm);
bool	windowdisplay(t_imgdata *data, t_line *line);
#endif