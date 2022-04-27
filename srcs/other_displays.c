/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_displays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 23:51:24 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/27 21:35:02 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	display_message(t_imgdata *data, bool death, float x_mod, float y_mod)
{
	size_t	x;
	size_t	y;
	float	display_x;
	float	display_y;

	x = 0;
	y = 0;
	display_x = data->width / x_mod;
	display_y = data->height / y_mod;
	data->img[GREY] = mlx_new_image(data->mlx, data->width, data->height);
	mlx_image_to_window(data->mlx, data->img[GREY], 0, 0);
	while (y < data->height)
	{
		while (x < data->width)
		{
			mlx_put_pixel(data->img[GREY], x, y, 0x303331);
			x++;
		}
		x = 0;
		y++;
	}
	if (death == true)
		data->xpm[SCREEN] = mlx_load_xpm42("textures/gameover.xpm42");
	else
		data->xpm[SCREEN] = mlx_load_xpm42("textures/youwon.xpm42");
	mlx_draw_texture(data->img[GREY], &data->xpm[SCREEN]->texture, \
									display_x + 70, display_y + 200);
	// data->img[SCREEN] = mlx_texture_to_image(data->mlx, &data->xpm[SCREEN]->texture);
	// mlx_image_to_window(data->mlx, data->img[SCREEN], display_x, display_y);
	if (death == true)
		mlx_put_string(data->mlx, "Press any key to continue...", display_x + 70, display_y + 200);
	else
		mlx_put_string(data->mlx, "Press any key to continue...", display_x, display_y + 100);
	usleep(10);
}
