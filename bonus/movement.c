/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:37:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/29 03:21:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	movement(t_imgdata *data, size_t x, size_t y)
{
	// if (data->img[CHAR]->instances[0].x >= 33 && data->img[CHAR]->instances[0].x <= 63)
	// 	x = 2;
	// if (data->img[CHAR]->instances[0].y >= 33 && data->img[CHAR]->instances[0].y <= 63)
	// 	y = 2;
	// if (data->img[CHAR]->instances[0].x % BLOK > BLOK / 2)
	// 	x++;
	// if (data->img[CHAR]->instances[0].y % BLOK > BLOK / 2)
	// 	y++;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) \
						&& data->map[y + 1][x] != '1')
		data->img[CHAR]->instances[0].y += BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A) \
							&& data->map[y][x] != '1')
		data->img[CHAR]->instances[0].x -= BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) \
							&& data->map[y][x + 1] != '1')
		data->img[CHAR]->instances[0].x += BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
		&& data->map[y][x] != '1' && (data->fly == true || 
		GRAV == 0))
		data->img[CHAR]->instances[0].y -= BLOK / FATASS;
}

void	movecounter(t_imgdata *data, size_t x, size_t y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down \
		(data->mlx, MLX_KEY_D) || mlx_is_key_down \
		(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx, MLX_KEY_W))
	{	
		if (x == data->old_x + 1 || x == data->old_x - 1 \
			|| y == data->old_y + 1 || y == data->old_y - 1)
		{
			data->old_x = x;
			data->old_y = y;
			data->count[MOVE]++;
		}
	}
}
