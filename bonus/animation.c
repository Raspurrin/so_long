/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:49:47 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/19 18:57:16 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * In movecounter() in movement.c the animate->length and animate-xy[1] are 
 * initalised based on if the character is moving or not. It takes different
 * positions from the same spritesheet, with different lengths of animation. 
 * This function basically changes the area it puts on the screen from that
 * same spritesheet every 5 frames and resets it to the starting location
 * at the end of the animation.
 */
void	animate_char(t_imgdata *data, t_animate *animate, size_t x, size_t y)
{
	const uint32_t	wh2[] = {32, 32};

	if ((animate->xy[0] - animate->start) >= animate->length)
		animate->xy[0] = animate->start;
	mlx_delete_image(data->mlx, data->img[CHAR]);
	data->img[CHAR] = mlx_texture_area_to_image(data->mlx, \
			&data->xpm[animate->dir]->texture, animate->xy, (uint32_t *)wh2);
	if (mlx_image_to_window(data->mlx, data->img[CHAR], x, y) == -1)
		(free_close_window(data, data->img[CHAR], "image_to_window failed"));
	mlx_set_instance_depth(data->img[CHAR]->instances, GHOSTCOUNT + 100);
	if (data->count[FRAME] % 7 == 0)
		animate->xy[0] += 50;
	data->count[FRAME]++;
}

/**
 * @param ghost The image of the ghost put on the screen, will differ depending
 * on which direction the ghost is moving. Decided in enemy_move() 
 * in enemy_interactions.c
 */
void	animate_ghosts(t_imgdata *data, mlx_texture_t *ghost, \
								t_enemy *enemy, size_t i)
{
	mlx_delete_image(data->mlx, data->enemy.ghost_img[i]);
	data->enemy.ghost_img[i] = mlx_texture_to_image(data->mlx, ghost);
	mlx_image_to_window(data->mlx, data->enemy.ghost_img[i], \
							enemy->x[0], enemy->y[0]);
	mlx_set_instance_depth(data->enemy.ghost_img[i]->instances, i + 100);
}
