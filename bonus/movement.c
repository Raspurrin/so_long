/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:37:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/17 01:15:00 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * Will change position of the character depending on 
 * which WASD key is pressed. An increased value of FATASS
 * causes slower movement. If gravity is off upward movement
 * is possible with W.
 */
void	movement(t_imgdata *data, size_t x, size_t y)
{

	if (mlx_is_key_down(data->mlx, MLX_KEY_S) \
						&& data->map[x + 1][x] != '1')
		data->img[CHAR]->instances[0].y += BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A) \
							&& data->map[y][x] != '1')
		data->img[CHAR]->instances[0].x -= BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) \
							&& data->map[y][x + 1] != '1')
		data->img[CHAR]->instances[0].x += BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
		&& data->map[y][x] != '1' && (data->fly == true || \
		GRAV == 0))
		data->img[CHAR]->instances[0].y -= BLOK / FATASS;
}

/**
 * Counts the movement of the character to be displayed on the screen.
 * Checks if one whole block has been traversed before counting the movement.
 * Also initialises different values as different animations are needed
 * depending on if the character is moving or not
 */
void	movecounter(t_imgdata *data, t_animate *animate, size_t x, size_t y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down \
		(data->mlx, MLX_KEY_D) || mlx_is_key_down \
		(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx, MLX_KEY_W))
	{	
		animate->length = 200;
		animate->xy[1] = 40;
		if (x >= data->old_x + BLOK || x <= data->old_x - BLOK \
			|| y >= data->old_y + BLOK || y <= data->old_y - BLOK)
		{
			data->old_x = x;
			data->old_y = y;
			data->count[MOVE]++;
		}
	}
	else
	{
		animate->length = 150;
		animate->xy[1] = 0;
	}
	animate->start = data->xy[0];
}
