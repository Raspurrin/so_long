/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity_jump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:51:55 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/18 02:15:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Initialises accel with a starting value or if jump_lock is activated,
 * keep decrementing the y position of the character with a decreasing value
 * to simulate the effect of gravity until accel reaches a preset max value.
 * And toggles flying mode with enter, a boolean used in the movement function
 */
static void	jump(t_imgdata *data)
{
	size_t	y_blok;

	y_blok = data->img[CHAR_R]->instances[0].y - (BLOK / data->accel);
	if (data->jump_lock == false)
		data->accel = ACCEL;
	else
	{
		if (data->accel >= JUMP_CAP || y_blok - BLOK / data->accel < 0)
			data->jump_lock = false;
		else
		{
			data->img[CHAR_R]->instances[0].y -= BLOK / data->accel;
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

/**
 * Pulls down the character every frame a certain amount unless he jumps.
 * Jumping only works if the character is right above a wall or tile. 
 * Jump_lock activates to execute the jump over several frames.
 */
void	gravity(t_imgdata *data, size_t x, size_t y)
{
	jump(data);
	if (data->map[y + 1][x] != '1' && GRAV == 1)
		data->img[CHAR_R]->instances[0].y += 3;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) && GRAV == 1 \
			&& data->map[y - 1][x] != '1' && data->map[y + 1][x] == '1')
		data->jump_lock = true;
}
