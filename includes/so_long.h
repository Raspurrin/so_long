/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/25 21:38:38 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/srcs/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# define BLOK 32
# define ENEMYCOUNT 0
# define LIVES 3

typedef enum move
{
	X,
	Y,
}	t_move;

typedef enum mlx_images
{
	CHAR,
	SLIME,
	BG,
	TILE,
	WALL,
	PICKUP,
	BRICK,
	DOOR,
	GHOST,
	STRMOVE,
	SCREEN,
	GREY,
	IMG_COUNT,
}	t_images;

typedef enum string
{
	LIFE,
	MOVE,
	STR_COUNT,
}	t_string;

typedef struct line
{
	size_t	count;
	size_t	size;
}	t_line;

typedef struct image_data
{
	mlx_t				*mlx;
	mlx_key_data_t		*keydata;
	char				**map;
	char				*bigass;
	int32_t				count[STR_COUNT];
	char				*str[STR_COUNT];
	char				*combstr[STR_COUNT];
	size_t				lives;

	mlx_texture_t		*ghost;
	xpm_t				*xpm[IMG_COUNT];
	mlx_image_t			*img[IMG_COUNT];
	t_line				line;
	size_t				enemy_x[ENEMYCOUNT];
	size_t				enemy_y[ENEMYCOUNT];
	size_t				move[ENEMYCOUNT];
	size_t				blok;
	size_t				collect;
	size_t				width;
	size_t				height;
	size_t				counter;
	size_t				enemy_max;
	int32_t				pid;
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
size_t	getncount(char *str, uint8_t chr);
bool	loading_images(t_imgdata *data, xpm_t **xpm);
bool	windowdisplay(t_imgdata *data, t_line *line);
void	texture_to_image(t_imgdata *data, xpm_t **xpm);
char	*read_file(int32_t fd);
void	free_2d(char **map);
bool	check_ext(char *file_name, char *ext);
char	**input_handler(int32_t fd, t_imgdata *data, t_line *line);
void	error_output(t_error *errors, t_line *line);
int32_t	graphics(t_imgdata *data, t_line *line);
void	images_to_window(t_imgdata *data, mlx_image_t **img, \
						t_line *line, size_t bs);
int32_t	find_c_instance(t_imgdata *data, size_t x_max, size_t y_max);
void	get_enemy_spawn(t_imgdata *data);
void	enemy_to_window(t_imgdata *data, size_t *x, size_t *y);
void	check_player_amount(t_error *errors, t_imgdata *data);
void	enemy_move(void	*data);
void	display_message(t_imgdata *data, bool death);
#endif