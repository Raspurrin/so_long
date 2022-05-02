/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_features.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:51:55 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/30 19:28:29 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	jump(t_imgdata *data)
{
	size_t	y;

	y = data->img[CHAR]->instances[0].y - (BLOK / data->accel);
	if (data->jump_lock == false)
		data->accel = ACCEL;
	else
	{
		if (data->accel >= JUMP_CAP || y <= 1)
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

void	animation(t_imgdata *data, size_t x, size_t y)
{
	const uint32_t	wh2[] = {32, 32};

	if ((data->xy[0] - data->char_start) == 200)
		data->xy[0] = data->char_start;
	mlx_delete_image(data->mlx, data->img[CHAR]);
	data->img[CHAR] = mlx_texture_area_to_image(data->mlx, \
						&data->xpm[CHAR]->texture, data->xy, (uint32_t *)wh2);
	mlx_image_to_window(data->mlx, data->img[CHAR], x, y);
	// (free_close_window(data, data->img[CHAR], "image_to_window failed"));
	mlx_set_instance_depth(data->img[CHAR]->instances, 200);
	if (data->count[FRAME] % 5 == 0)
		data->xy[0] += 50;
	data->count[FRAME]++;
}
