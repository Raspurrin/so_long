/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:37:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/04 06:06:05 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * move 1 == down 	(y +) 
 * move 2 == left 	(x -)
 * move 3 == right 	(x +)
 * move 4 == up 	(y -)
 */
void	move_compare(t_imgdata *data, size_t x, size_t y, int16_t move)
{
	size_t	i;

	i = 0;
	while (i < data->obs_amount[OBS_1])
	{
		if (move == 1 && y + BLOK < data->obs_1[i].y_start)
		{
			data->img[CHAR]->instances[0].y += BLOK / FATASS;
			break ;
		}
		else if (move == 2 && x - BLOK < data->obs_1[i].x_end)
		{
			data->animate.dir = CHAR_L;
			data->img[CHAR]->instances[0].x -= BLOK / FATASS;
			break ;
		}
		else if (move == 3 && x + BLOK < data->obs_1[i].x_start)
		{
			data->animate.dir = CHAR;
			data->img[CHAR]->instances[0].x += BLOK / FATASS;
			break ;
		}
		else if (move == 4 && y - BLOK > data->obs_1[i].y_end + 1 && \
			data->fly == true || GRAV == 0)
		{
			data->img[CHAR]->instances[0].y -= BLOK / FATASS;
			break ;
		}
		i++;
	}
}

/**
 * Will change position of the character depending on 
 * which WASD key is pressed. An increased value of FATASS
 * causes slower movement. If gravity is off upward movement
 * is possible with W.
 */
void	movement(t_imgdata *data, size_t x, size_t y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_compare(data, x, y, 1);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_compare(data, x, y, 2);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_compare(data, x, y, 3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_compare(data, x, y, 4);
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

// void	move_compare(t_imgdata *data, size_t x, size_t y, int16_t move)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < data->obs_amount[OBS_1])
// 	{
// 		if (move == 1 && y + BLOK < data->obs_1[i].y_start)
// 			data->img[CHAR]->instances[0].y += BLOK / FATASS;
// 		else if (move == 2 && x - BLOK > data->obs_1[i].x_end)
// 		{
// 			data->animate.dir = CHAR_L;
// 			data->img[CHAR]->instances[0].x -= BLOK / FATASS;
// 		}
// 		else if (move == 3 && x + BLOK < data->obs_1[i].x_start)
// 		{
// 			data->animate.dir = CHAR;
// 			data->img[CHAR]->instances[0].x += BLOK / FATASS;
// 		}
// 		else if (move == 4 && y - BLOK > data->obs_1[i].y_end && \
// 			data->fly == true || GRAV == 0)
// 			data->img[CHAR]->instances[0].y -= BLOK / FATASS;
// 		i++;
// 	}
// }

