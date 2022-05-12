/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:37:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/11 19:34:57 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	movement(t_imgdata *data, size_t x, size_t y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		kill(0, SIGKILL);
	}
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
 * @brief Counts the movement of the character to be displayed on the screen.
 * Checks if one whole block has been traversed before counting the movement.
 * @param x Current x position of character.
 * @param y Current y position of character.
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