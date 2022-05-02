/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/02 14:11:36 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <stdio.h>
# include <signal.h>
# define BLOK 32
# define ENEMYCOUNT 330
# define LIVES 100
# define ACCEL 1
# define ACCEL_MOD 1.3
# define JUMP_CAP 100
# define FATASS 10
# define FATBOO 200
# define SPEED 18
# define IMMORTAL 1
# define KILL 1
# define GRAV 1

typedef enum move
{
	X,
	Y,
}	t_move;

typedef enum mlx_images
{
	STRLIFE,
	STRMOVE,
	CHAR,
	SLIME,
	BG,
	TILE,
	WALL,
	PICKUP,
	BRICK,
	DOOR,
	GHOST,
	SCREEN,
	GREY,
	IMG_COUNT,
}	t_images;

typedef enum string
{
	LIFE,
	MOVE,
	FRAME,
	STR_COUNT,
}	t_string;

typedef struct line
{
	size_t	count;
	size_t	size;
}	t_line;

typedef struct enemy
{
	size_t				current_time;
	size_t				enemy_max;
	size_t				enemy_time;
	size_t				enemy_x[ENEMYCOUNT];
	size_t				enemy_y[ENEMYCOUNT];
	size_t				excep_count;
	size_t				excep[ENEMYCOUNT];
	size_t				move[ENEMYCOUNT];
	mlx_image_t			*img[ENEMYCOUNT];
	bool				time_lock;
}	t_enemy;

typedef struct image_data
{
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
	size_t				height;
	mlx_image_t			*img[IMG_COUNT];
	mlx_key_data_t		*keydata;
	bool				jump_lock;
	int32_t				jump_time;
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
	size_t				width;
	xpm_t				*xpm[IMG_COUNT];
	uint32_t			xy[2];
}	t_imgdata;

typedef struct error_cases
{
	bool	error;
	bool	file_name;
	bool	walls;
	bool	cpe;
	bool	different_input;
	bool	rectangular;
	bool	morecharacters;
	bool	enemyoverflow;
}	t_error;

/**
 * @brief Iterates through an array of strings and frees every string
 * @param map 2D array
 * @return NULL
 */
void	animation(t_imgdata *data, size_t x, size_t y);
bool	check_ext(char *file_name, char *ext);
void	check_player_amount(t_error *errors, t_imgdata *data);
void	collect(t_imgdata *data, size_t x, size_t y);
void	display_message(t_imgdata *data, bool death, float x_mod, float y_mod);
void	display_string(t_imgdata *data, int32_t str_img, size_t x, char *str);
void	end(mlx_key_data_t keydata, void *data);
void	enemies(t_imgdata *data, t_enemy *enemy, size_t x, size_t y);
bool	enemy_to_window(t_imgdata *data);
void	error_output(t_error *errors, t_line *line);
void	error_close_window(t_imgdata *data, char *str);
int32_t	find_c_instance(t_imgdata *data, size_t x_max, size_t y_max);
void	free_2d(char **map);
bool	free_array(void *arr, char *str);
void	free_close_window(t_imgdata *data, void *var, char *str);
void	gravity(t_imgdata *data, size_t x, size_t y);
size_t	getncount(char *str, uint8_t chr);
size_t	getncount(char *str, uint8_t chr);
void	get_enemy_spawn(t_imgdata *data);
int32_t	graphics(t_imgdata *data, t_line *line);
bool	images_to_window(t_imgdata *data, mlx_image_t **img, size_t i);
char	**input_handler(int32_t fd, t_imgdata *data, \
						t_line *line, t_enemy *enemy);
bool	loading_images(t_imgdata *data, xpm_t **xpm);
void	movement(t_imgdata *data, size_t x, size_t y);
void	movecounter(t_imgdata *data, size_t x, size_t y);
char	*read_file(int32_t fd);
bool	texture_to_image(t_imgdata *data, xpm_t **xpm);
bool	windowdisplay(t_imgdata *data, t_line *line);
#endif