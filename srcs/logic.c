/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/12 19:46:07 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"

void	images_to_window(t_imgdata *data, char **map, \
						t_line *line)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	mlx_image_to_window(data->mlx, data->bg, 0, 0);
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				if (x == 0 || y == 0 || y == line->count || x == line->size - 1)
				{
					mlx_image_to_window(data->mlx, data->wall, x * 32, y * 32);
					// mlx_set_instance_depth(&data->wall->instances[a], 20);
				}
				else
					mlx_image_to_window(data->mlx, data->tile, x * 32, y * 32);
			}
			if (map[y][x] == 'C')
				mlx_image_to_window(data->mlx, data->pickup, x * 32, y * 32);
			if (map[y][x] == 'E')
				mlx_image_to_window(data->mlx, data->pickup, x * 32, y * 32);
			if (map[y][x] == 'P')
				mlx_image_to_window(data->mlx, data->character, x * 32, y * 32);
			x++;
		}
		x = 0;
		y++;
	}
}
