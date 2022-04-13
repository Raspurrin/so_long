/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/14 01:04:20 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42.h"
# include <stdio.h>

typedef struct xpm
{
	
} t_xpm;

typedef struct image_data
{
	mlx_t			*mlx;
	mlx_key_data_t	*keydata;
	xpm_t			*xpm_char;
	xpm_t			*xpm_bg;
	xpm_t			*xpm_slime;
	xpm_t			*xpm_tile;
	xpm_t			*xpm_wall;
	xpm_t			*xpm_pickup;
	xpm_t			*xpm_brick;
	mlx_image_t		*character;
	mlx_image_t		*slime;
	mlx_image_t		*bg;
	mlx_image_t		*tile;
	mlx_image_t		*wall;
	mlx_image_t		*pickup;
	mlx_image_t		*brick;
	size_t			block;
	uint8_t			*startingpoint;
	size_t			blok;
	char			**map;
	size_t			collect;
	size_t			width;
	size_t			height;
}	t_imgdata;

typedef struct line
{
	size_t	count;
	size_t	size;
}	t_line;

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
void	images_to_window(t_imgdata *data, \
						t_line *line, size_t bs);
#endif