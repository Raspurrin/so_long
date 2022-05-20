/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/20 05:24:08 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	if (data->map[y][x] == 'C')
	{
		i = find_c_instance((t_imgdata *)data, y * (data->line.size + 1) + x);
		data->map[y][x] = 'K';
		mlx_set_instance_depth(&data->img[PICKUP]->instances[i], -1000);
		data->collect--;
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
