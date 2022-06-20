/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:42:17 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/20 16:05:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * @param x - x position of the centre of the circle.
 * @param y - y position of the centre of the circle. 
 * @param radius
 * are drawn.
*/
void	circle(t_imgdata *data, size_t c_x, size_t c_y, int32_t radius)
{
	size_t	i;
	size_t	x;
	size_t	y;
	
	i = 0;
	radius = radius + mlx_get
	data->img[CIRCLE] = mlx_new_image(data->mlx, data->width, data->height);
	while (data->bigass[i])
	{
		x = i % (data->line.size + 1);
		y = i / (data->line.size + 1);
		if (!(x + y == ((c_x + c_y) - radius)) || !(x + y == ((c_x + c_y) + radius)))
			mlx_put_pixel(data->img[CIRCLE], x, y, 0x4c4c4c33);
		i++;
	}
	return (0);
}