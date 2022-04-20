/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/20 16:39:55 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"

void	get_enemy_spawn(t_imgdata *data)
{
	size_t	i;
	size_t	index;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		index = rand() % ((data->line.size + 2) * (data->line.count - 1));
		while (data->bigass[index] != '0')
		{
			index++;
			if (!(data->bigass[index]))
				index = 0;
		}
		data->enemy_x[i] = index % data->line.size;
		data->enemy_y[i] = index / data->line.size;
		i++;
	}
}

void	images_to_window(t_imgdata *data, mlx_image_t **img, \
						t_line *line, size_t bs)
{
	size_t	x;
	size_t	y;
	size_t	i;

	x = 0;
	y = 0;
	i = 0;
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
			else if (data->map[y][x] == 'C')
				mlx_image_to_window(data->mlx, img[PICKUP], x * bs, y * bs);
			else if (data->map[y][x] == 'P')
				mlx_image_to_window(data->mlx, img[CHAR], x * bs, y * bs);
			else if (data->map[y][x] == 'E')
				mlx_image_to_window(data->mlx, img[DOOR], x * bs, y * bs);
			while (i < ENEMYCOUNT)
			{
				if (y == data->enemy_y[i] && x == data->enemy_x[i] && i < ENEMYCOUNT)
					mlx_image_to_window(data->mlx, img[GHOST], x * bs, y * bs);
				i++;
			}
			i = 0;
			x++;
		}
		x = 0;
		y++;
	}
}

int32_t	find_instance(t_imgdata *data, size_t x_max, size_t y_max)
{
	size_t	x;
	size_t	y;
	int32_t	instance;

	x = 0;
	y = 0;
	instance = 0;
	while (y <= y_max)
	{
		while (x <= data->line.size)
		{
			if (data->map[y][x] == 'C' || data->map[y][x] == 'K')
				instance++;
			x++;
			if (y == y_max && x == x_max - 1)
				break ;
		}
		x = 0;
		y++;
	}
	return (instance);
}
