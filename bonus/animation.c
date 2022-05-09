/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:49:47 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/10 00:03:09 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	animation(t_imgdata *data, t_animate *animate, size_t x, size_t y)
{
	const uint32_t	wh2[] = {32, 32};

	if ((animate->xy[0] - animate->start) >= animate->length)
		animate->xy[0] = animate->start;
	mlx_delete_image(data->mlx, data->img[CHAR]);
	data->img[CHAR] = mlx_texture_area_to_image(data->mlx, \
						&data->xpm[CHAR]->texture, animate->xy, (uint32_t *)wh2);
	mlx_image_to_window(data->mlx, data->img[CHAR], x, y);
	// (free_close_window(data, data->img[CHAR], "image_to_window failed"));
	mlx_set_instance_depth(data->img[CHAR]->instances, GHOSTCOUNT + 100);
	if (data->count[FRAME] % 5 == 0)
		animate->xy[0] += 50;
	data->count[FRAME]++;
}

void	animate_ghosts(t_imgdata *data, mlx_texture_t *ghost, \
								size_t x, size_t y, size_t i)
{
	mlx_delete_image(data->mlx, data->enemy.img[i]);
	data->enemy.img[i] = mlx_texture_to_image(data->mlx, ghost);
	mlx_image_to_window(data->mlx, data->enemy.img[i], x, y);
	mlx_set_instance_depth(data->enemy.img[i]->instances, i + 100);
}
