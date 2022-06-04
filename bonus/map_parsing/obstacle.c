/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obstacle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 05:45:33 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/04 22:29:04 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"


/**
 * x_start/y_start -> o---o  <- x_end
 * 					  |   |
 * 			y_end->	  o---o
 * Doesn't particularly make sense actually... 
 */
void	init_coords(t_imgdata *data, size_t index, int32_t obs_index, \
																t_coords *obs)
{
	obs[obs_index].x_start = (index % (data->line.size + 1) * BLOK);
	obs[obs_index].y_start = (index / (data->line.size + 1)) * BLOK;
	obs[obs_index].x_end = ((index % (data->line.size + 1)) + 1) * BLOK;
	obs[obs_index].y_end = ((index / (data->line.size + 1)) + 1) * BLOK;
	obs[obs_index].instance = obs_index;
}

void	obstacle_pickup(t_imgdata *data)
{
	size_t	i;
	size_t	j;
	// size_t	k;
	size_t	l;
	ssize_t	x;
	ssize_t	y;

	i = 0;
	j = 0;
	// k = 0;
	l = 0;
	data->obs_pickup = ft_calloc(data->pickup_max, sizeof(t_coords));
	// data->obs_tile = ft_calloc(data->tile_count, sizeof(t_coords));
	data->obs_1 = ft_calloc(data->obs_amount[OBS_1], sizeof(t_coords));
	data->excep_pickup = ft_calloc(data->pickup_max, sizeof(bool) + 1);
	while (data->bigass[i])
	{
		x = i % (data->line.size + 1);
		y = i / (data->line.size + 1);
		if (data->bigass[i] == 'C')
			init_coords(data, i, j++, data->obs_pickup);
		if (data->bigass[i] == '1')
		{
			init_coords(data, i, l++, data->obs_1);
			// if (x != 0 && y != 0 && x != line->size - 1 && y != line->count)
			// 	init_coords(data, i, k++, data->obs_tile);
		}
		i++;
	}
}
