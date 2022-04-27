/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:51:55 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/27 18:11:18 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


// data->map[y - (BLOK / data->accel)][x]  != '1'
//  && y - BLOK / data->accel > 1
// 	while (data->jump_lock == true)
static void	jump(t_imgdata *data)
{
	if (data->jump_lock == false)
		data->accel = ACCEL;
	else
	{
		if (data->accel >= JUMP_CAP)
			data->jump_lock = false;
		data->img[CHAR]->instances[0].y -= BLOK / data->accel;
		data->accel *= ACCEL_MOD;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER) && FLY == 1)
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
	if (data->map[y + 1][x] != '1')
		data->img[CHAR]->instances[0].y += 3;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
			&& data->map[y - 1][x] != '1' && data->map[y + 1][x] == '1')
	{
			data->jump_lock = true;
			data->jump_time = mlx_get_time();
	}
}

// if ((mlx_is_key_down(data->mlx, MLX_KEY_W) && data->map[y + 1][x] == '1') || \
// 		(mlx_get_time() >= (data->jump_time + 1) && mlx_is_key_down(data->mlx, MLX_KEY_W)))

void	animation(t_imgdata *data, size_t x, size_t y)
{
	uint32_t		wh2[] = {32, 32};


	if ((data->xy[0] - data->char_start) == 200)
		data->xy[0] = data->char_start;
	mlx_delete_image(data->mlx, data->img[CHAR]);
	data->img[CHAR] = mlx_texture_area_to_image(data->mlx, \
						&data->xpm[CHAR]->texture, data->xy, (uint32_t *)wh2);
	mlx_image_to_window(data->mlx, data->img[CHAR], 100, 100);
	if (data->counter % 5 == 0)
		data->xy[0] += 50;
	data->counter++;
	// data->startingpoint = *data->img[CHAR]->pixels;
	// while ((*data->img[CHAR]->pixels - data->startingpoint) <= 40)
	// 	data->img[CHAR]->pixels += ((uint8_t)(mlx_get_time() % 4 * 10));
	// *data->img[CHAR]->pixels += 50;
	// *data->xpm[CHAR]->pixels += ((uint8_t)(mlx_get_time() % 4 * 10));
	// data->img[CHAR]->pixels += 40;
}
	// uint8_t		*startingpoint;

 	// startingpoint = data->img[CHAR]->pixels;
 	// uint8_t	test = ((uint8_t)(mlx_get_time() % 4 * 10));
 	// printf("%d", mlx_get_time() % 4 * 10);
	//  if ((*data->img[CHAR]->pixels - data->startingpoint) >= 60)
	// 		data->img[CHAR]->pixels = &data->startingpoint;
	// data->img[CHAR]->pixels += ((uint8_t)(mlx_get_time() % 4 * 10));
	// ---------------------------------------
	// uint8_t	nbr;
	// uint8_t	*pixel = &nbr;

	// nbr = 50;
	// while (*pixel <= 40)
	// {
	// 	*pixel = (mlx_get_time() * 10) % 40;
		// printf("%hhu", *pixel);
	// data->img[CHAR]->pixels = &nbr;
	// }