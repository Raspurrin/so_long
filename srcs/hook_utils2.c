/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:51:55 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/27 00:00:46 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	gravity(t_imgdata *data, size_t x, size_t y)
{
	if (data->jump_lock == false)
		data->accel = ACCEL;
	else
	{
		if (data->accel >= 100)
			data->jump_lock = false;
		data->img[CHAR]->instances[0].y -= BLOK / data->accel;
		data->accel *= 1.5;
	}
	if (data->map[y + 1][x] != '1')
		data->img[CHAR]->instances[0].y += 3;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
			&& data->map[y - 1][x] != '1' && data->map[y + 1][x] == '1')
	{
			data->jump_lock = true;
			data->jump_time = mlx_get_time();
	}
}
