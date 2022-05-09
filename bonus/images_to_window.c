/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_to_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:40:13 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/08 22:03:30 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	walls_and_tiles(t_imgdata *data, size_t i, size_t x, size_t y)
{
	if (data->bigass[i] == '1')
	{
		if (x == 0 || y == 0 || y == data->line.count \
							|| x == data->line.size - 1)
		{
			if (mlx_image_to_window(data->mlx, data->img[WALL], \
												x * BLOK, y * BLOK) == -1)
				return (free_array(data->img, "image_to_window failed"), false);
		}
		else
			if (mlx_image_to_window(data->mlx, data->img[TILE], \
												x * BLOK, y * BLOK) == -1)
				return (free_array(data->img, "image_to_window failed"), false);
	}
	return (true);
}

static bool	images_to_window2(t_imgdata *data, size_t x, size_t y, \
													int32_t macro)
{
	if (macro >= PICKUP && macro <= DOOR)
	{
		if (mlx_image_to_window(data->mlx, data->img[macro], \
												x * BLOK, y * BLOK) == -1)
			return (free_array(data->img, "image_to_window failed"), false);
	}
	return (true);
}

bool	images_to_window(t_imgdata *data, size_t i)
{
	size_t	x;
	size_t	y;
	int32_t	macro;

	if (mlx_image_to_window(data->mlx, data->img[BG], 0, 0) == -1)
		return (free_close_window(data, data->img[BG], \
						"image_to_window failed"), 0);
	while (data->bigass[i])
	{
		macro = DOOR + 1;
		x = i % (data->line.size + 1);
		y = i / (data->line.size + 1);
		if (data->bigass[i] == '1')
		{
			if (!(walls_and_tiles(data, i, x, y)))
				return (false);
		}
		else if (data->bigass[i] == 'C')
			macro = PICKUP;
		else if (data->bigass[i] == 'P')
			macro = CHAR;
		else if (data->map[y][x] == 'E')
			macro = DOOR;
		if (!(images_to_window2(data, x, y, macro)))
			return (false);
		i++;
	}
	return (true);
}

bool	enemy_to_window(t_imgdata *data, t_enemy *enemy)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	while (i < GHOSTCOUNT)
	{
		x = enemy->x[i];
		y = enemy->y[i];
		if (mlx_image_to_window(data->mlx, enemy->img[i], \
												x * BLOK, y * BLOK) == -1)
			return (free_array(data->img, "image_to_window failed"), false);
		i++;
	}
	return (true);
}
