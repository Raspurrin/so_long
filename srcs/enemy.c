/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/26 20:04:31 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_enemy_spawn(t_imgdata *data)
{
	size_t	i;
	size_t	index;

	i = 0;
	while (i < ENEMYCOUNT && i < data->enemy_max)
	{
		index = rand() % ((data->line.size + 2) * (data->line.count - 1));
		while (data->bigass[index] != '0' && data->bigass[index])
		{
			index++;
			if (!(data->bigass[index]))
				index = 0;
		}
		if (index != 0)
		{
			data->enemy_x[i] = index % data->line.size;
			data->enemy_y[i] = index / data->line.size;
			i++;
		}
	}
}

void	enemy_to_window(t_imgdata *data, \
						size_t *x, size_t *y)
{
	size_t	i;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		if (*y == data->enemy_y[i] && *x == data->enemy_x[i] \
			&& i < ENEMYCOUNT && i < data->enemy_max)
		{
			mlx_image_to_window(data->mlx, data->img[GHOST], \
								*x * BLOK, *y * BLOK);
		}
		i++;
	}
	return ;
}
