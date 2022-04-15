/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/15 00:38:24 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"

void	images_to_window(t_imgdata *data, mlx_image_t **img, \
						t_line *line, size_t bs)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
			{
				if (x == 0 || y == 0 || y == line->count || x == line->size - 1)
					mlx_image_to_window(data->mlx, img[WALL], x * bs, y * bs);
				else
					mlx_image_to_window(data->mlx, img[TILE], x * bs, y * bs);
			}
			if (data->map[y][x] == 'C')
				mlx_image_to_window(data->mlx, img[PICKUP], x * bs, y * bs);
			// if (data->map[y][x] == 'E')
			// 	mlx_image_to_window(data->mlx, data->pickup, x * bs, y * bs);
			if (data->map[y][x++] == 'P')
				mlx_image_to_window(data->mlx, img[CHAR], x * bs, y * bs);
		}
		x = 0;
		y++;
	}
}

/**
 * 
 * 
 */