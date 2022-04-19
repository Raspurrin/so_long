/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/19 21:14:25 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42.h"
# include <stdio.h>

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
	IMG_COUNT,
}	t_images;

typedef struct line
{
	size_t	count;
	size_t	size;
}	t_line;

typedef struct image_data
{
	int					*nbrs;
	mlx_t				*mlx;
	mlx_key_data_t		*keydata;
	xpm_t				*xpm[IMG_COUNT];
	mlx_image_t			*img[IMG_COUNT];
	t_line				line;
	size_t				blok;
	size_t				collect;
	size_t				width;
	size_t				height;
	char				**map;
	char				*bigass;
	int32_t				movecount;
	size_t				enemy_x[2];
	size_t				enemy_y[2];
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
}	t_error;

/**
 * @brief Iterates through an array of strings and frees every string
 * @param map 2D array
 * @return NULL
 */
char	*read_file(int32_t fd);
void	free_2d(char **map);
bool	check_ext(char *file_name, char *ext);
char	**input_handler(int32_t fd, t_imgdata *data, t_line *line);
void	error_output(t_error *errors, t_line *line);
int32_t	graphics(t_imgdata *data, t_line *line);
void	images_to_window(t_imgdata *data, mlx_image_t **img, \
						t_line *line, size_t bs);
int32_t	find_instance(t_imgdata *data, size_t x_max, size_t y_max);
void	get_enemy_spawn(t_imgdata *data);
#endif