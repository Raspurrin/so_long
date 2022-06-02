/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/02 21:08:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * If player encounters a collectible, check which instance of the texture
 * was used to change the z-axis/depth of the image to put it behind the
 * background. Then changes the character on the 2D map, so the same condition
 * cannot be true anymore. And decreasesing the count of the collectibles
 * for the end condition.
 */
void	collect(t_imgdata *data, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	while (i < data->pickup_max)
	{
		if ((x >= data->obs[i].x_start && x <= data->obs[i].x_end) && \
			(y >= data->obs[i].y_start && y <= data->obs[i].y_end) && \
			data->pickup_excep[i] == false)
		{
			mlx_set_instance_depth(&data->img[PICKUP]->instances[i], -1100);
			data->pickup_count++;
			data->pickup_excep[i] = true;
		}
		i++;
	}
}

/**
 * itterates through the map and counts every occurance of the collectibles
 * until the position of the collectible that was interacted with.
 */
int32_t	find_c_instance(t_imgdata *data, size_t index)
{
	size_t	i;
	int32_t	instance;

	i = 0;
	instance = 0;
	while (i <= index)
	{
		if (data->bigass[i] == 'C' || data->bigass[i] == 'K')
			instance++;
		i++;
		if (i == index - 1)
			break ;
	}
	return (instance);
}
