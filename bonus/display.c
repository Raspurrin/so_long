/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 23:51:24 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/29 03:21:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	grey_screen(t_imgdata *data)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	data->img[GREY] = mlx_new_image(data->mlx, data->width, data->height);
	mlx_image_to_window(data->mlx, data->img[GREY], 0, 0);
		// (free_close_window(data, data->img[GREY], "image_to_window failed"));
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
}

void	display_message(t_imgdata *data, bool death, float x_mod, float y_mod)
{
	float	display_x;
	float	display_y;

	display_x = data->width / x_mod;
	display_y = data->height / y_mod;
	grey_screen(data);
	if (death == true)
		data->xpm[SCREEN] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/gameover.xpm42");
	else
		data->xpm[SCREEN] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/youwon.xpm42");
	// mlx_draw_texture(data->img[GREY], &data->xpm[SCREEN]->texture, \
	// 								display_x + 70, display_y + 200);
		// (free_close_window(data, data->img[GREY], "mlx_draw_texture failed"));
	data->img[SCREEN] = mlx_texture_to_image(data->mlx, \
							&data->xpm[SCREEN]->texture);
	mlx_image_to_window(data->mlx, data->img[SCREEN], \
										display_x, display_y);
		// (free_close_window(data, data->img[SCREEN], "image_to_window failed"));
	if (death == true)
		mlx_put_string(data->mlx, "Press any key to continue...", \
									display_x + 70, display_y + 200);
	else
		mlx_put_string(data->mlx, "Press any key to continue...", \
										display_x, display_y + 100);
	usleep(10);
}

void	display_string(t_imgdata *data, int32_t str_img, size_t x, char *str)
{
	if (data->img[str_img])
		mlx_delete_image(data->mlx, data->img[str_img]);
	data->str[str_img] = ft_itoa(data->count[str_img]);
	// if (!(data->str[str_img]))
	// 	return (free_close_window(data, data->str, \
	// 								"Error\nFailed string"));
	data->combstr[str_img] = ft_strjoin(str, data->str[str_img]);
	// if (!(data->combstr[str_img]))
	// 	return (free_close_window(data, data->combstr, \
	// 								"Error\nFailed string"));
	data->img[str_img] = mlx_put_string(data->mlx, \
								data->combstr[str_img], x, 0);
	mlx_set_instance_depth(data->img[str_img]->instances, 200);
}
