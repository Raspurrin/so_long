/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_to_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:40:13 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/10 02:52:52 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * I have different images for when '1' appears. A wall for the outer
 * edges and a platform for within, so I'm just checking those positions.
 */
bool	walls_and_tiles(t_imgdata *data, size_t i, ssize_t x, ssize_t y)
{
	if (data->bigass[i] == '1')
	{
		if (x == 0 || y == 0 || y == data->line.count \
							|| x == data->line.size - 1)
		{
			if (mlx_image_to_window(data->mlx, data->img[WALL], \
												x * BLOK, y * BLOK) == -1)
				return (free_array(data->img, "image_to_window failed", \
															data), false);
		}
		else
		{
			if (mlx_image_to_window(data->mlx, data->img[TILE], \
												x * BLOK, y * BLOK) == -1)
				return (free_array(data->img, "image_to_window failed", \
															data), false);
			data->tile_count++;
		}
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
			return (free_array(data->img, "image_to_window failed", \
														data), false);
	}
	return (true);
}

/**
 * Goes through the map in a big ass string, while keeping track
 * of the current x and y positions by a calculation: 
 * Ex: i = 8: 
 * 11111 x == (i % 5 = 3)
 * 10*C1 y == (i / 5 = 1.6, so 1)
 * Depending on the character encountered, will put a different image
 * to the window at that position.
 */
bool	images_to_window(t_imgdata *data, size_t i)
{
	size_t	x;
	size_t	y;
	int32_t	macro;

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

/**
 * Will use the established positions from arrays initialised in 
 * get_ghost_spawn and put those images on the screen
 */
bool	random_to_window(t_imgdata *data, ssize_t *index, size_t max_count, \
															mlx_image_t **img)
{
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	y;

	i = 0;
	while (i < max_count)
	{
		j = i;
		if (!img[i])
			j = 0;
		x = index[i] % (data->line.size + 1);
		y = index[i] / (data->line.size + 1);
		if (mlx_image_to_window(data->mlx, img[j], \
												x * BLOK, y * BLOK) == -1)
			return (free_array(data->img, "image_to_window failed", \
														data), false);
		i++;
	}
	return (true);
}
