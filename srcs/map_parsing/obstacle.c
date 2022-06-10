/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obstacle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 05:45:33 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/05 23:45:30 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * x_start/y_start -> o---o  <- x_end
 * 					  |   |
 * 			y_end->	  o---o
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

	i = 0;
	j = 0;
	data->obs_pickup = ft_calloc(data->pickup_max, sizeof(t_coords));
	data->excep_pickup = ft_calloc(data->pickup_max, sizeof(bool) + 1);
	while (data->bigass[i])
	{
		if (data->bigass[i] == 'C')
			init_coords(data, i, j++, data->obs_pickup);
		i++;
	}
}
