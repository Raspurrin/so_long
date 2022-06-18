/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:37:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/18 02:15:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Will change position of the character depending on 
 * which WASD key is pressed. An increased value of FATASS
 * causes slower movement. If gravity is off upward movement
 * is possible with W.
 */
void	movement(t_imgdata *data, size_t x, size_t y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) \
						&& data->map[y + 1][x] != '1')
		data->img[CHAR_R]->instances[0].y += BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A) \
							&& data->map[y][x] != '1')
		data->img[CHAR_R]->instances[0].x -= BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) \
							&& data->map[y][x + 1] != '1')
		data->img[CHAR_R]->instances[0].x += BLOK / FATASS;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
		&& data->map[y][x] != '1' && (data->fly == true || \
		GRAV == 0))
		data->img[CHAR_R]->instances[0].y -= BLOK / FATASS;
}

/**
 * Counts the movement of the character to be displayed on the screen.
 * Checks if one whole block has been traversed before counting the movement.
 * Also initialises different values as different animations are needed
 * depending on if the character is moving or not
 */
void	movecounter(t_imgdata *data, size_t x, size_t y)
{
	if ((mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down \
		(data->mlx, MLX_KEY_D) || mlx_is_key_down (data->mlx, MLX_KEY_A) \
		|| mlx_is_key_down(data->mlx, MLX_KEY_W)) && \
		(x >= data->old_x + BLOK || x <= data->old_x - BLOK \
			|| y >= data->old_y + BLOK || y <= data->old_y - BLOK))
	{
		data->old_x = x;
		data->old_y = y;
		write(1, "movement: ", 10);
		ft_putnbr_fd(data->count[MOVE], 1);
		write(1, "\n", 1);
		data->count[MOVE]++;
	}
}
