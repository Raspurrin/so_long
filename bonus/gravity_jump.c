/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity_jump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:51:55 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/09 21:51:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	jump(t_imgdata *data)
{
	size_t	y_blok;

	// || data->map[y - 1][x] == '1')
	y_blok = data->img[CHAR]->instances[0].y - (BLOK / data->accel);
	if (data->jump_lock == false)
		data->accel = ACCEL;
	else
	{
		if (data->accel >= JUMP_CAP || y_blok - BLOK / data->accel < 0)
			data->jump_lock = false;
		else
		{
			data->img[CHAR]->instances[0].y -= BLOK / data->accel;
			data->accel *= ACCEL_MOD;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
	{
		if (data->fly == false)
			data->fly = true;
		else
			data->fly = false;
	}
}

void	gravity(t_imgdata *data, size_t x, size_t y)
{
	jump(data);
	if (data->map[y + 1][x] != '1' && GRAV == 1)
		data->img[CHAR]->instances[0].y += 3;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) && GRAV == 1 \
			&& data->map[y - 1][x] != '1' && data->map[y + 1][x] == '1')
	{
			data->jump_lock = true;
			data->jump_time = mlx_get_time();
	}
}
