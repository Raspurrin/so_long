/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/06 22:09:59 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42.h"
# include <stdio.h>

typedef struct image_data
{
	mlx_t			*mlx;
	mlx_key_data_t	*keydata;
	mlx_image_t		*img;
}	t_imgdata;

typedef struct error_cases
{
	bool	error;
	bool	file_name;
	bool	walls;
	bool	cpe;
	bool	different_input;
	bool	rectangular;
}	t_error;

/**
 * @brief Iterates through an array of strings and frees every string
 * @param map 2D array
 * @return NULL
 */

char	*read_file(int32_t fd, char *line);
void	free_2d(char **map);
bool	check_ext(char *file_name, char *ext);
char	**input_handler(int32_t fd, char **map);
void	error_output(t_error *errors, size_t linecount);
int32_t	graphics(void);

#endif