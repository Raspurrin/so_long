/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/12 00:36:12 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	end(mlx_key_data_t keydata, void *data)
{
	t_imgdata *const	data2 = data;

	if (mlx_is_key_down(data2->mlx, keydata.key))
		mlx_close_window(data2->mlx);
	kill(data2->pid, SIGKILL);
	exit(0);
}

void	collect(t_imgdata *data, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	if (data->map[y][x] == 'C')
	{
		i = find_c_instance((t_imgdata *)data, x, y);
		data->map[y][x] = 'K';
		mlx_set_instance_depth(&data->img[PICKUP]->instances[i], -1);
		data->collect--;
	}
}

int32_t	find_c_instance(t_imgdata *data, size_t x_max, size_t y_max)
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
