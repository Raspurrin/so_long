/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 23:51:24 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/31 03:15:59 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * Will draw pixels on an image the size of the window with the provided colour
 * @param macro enum of the image used to draw colour on
 * @param colour colour channels being in this order: RGBA, each one byte 
 * stored into one 4 byte integer passed as a hex value prefixed with 0x
 */
void	colour_screen(t_imgdata *data, int32_t macro, int32_t colour)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	data->img[macro] = mlx_new_image(data->mlx, data->width, data->height);
	if (mlx_image_to_window(data->mlx, data->img[macro], 0, 0) == -1)
		(free_close_window(data, data->img[GREY], "image_to_window failed"));
	while (y < data->height)
	{
		while (x < data->width)
		{
			mlx_put_pixel(data->img[macro], x, y, colour);
			x++;
		}
		x = 0;
		y++;
	}
}

/**
 * Will colour the screen and display a certain message depending 
 * on game condition, then freezes everything a few miliseconds.
 * @param death if true displays death message, otherwise the win message
 * @param x_mod x-axis offset
 * @param y_mod y-axis offset
 */
void	display_message(t_imgdata *data, bool death, float x_mod, float y_mod)
{
	float	display_x;
	float	display_y;

	display_x = data->width / x_mod;
	display_y = data->height / y_mod;
	colour_screen(data, GREY, 0x303331);
	if (death == true)
		data->xpm[SCREEN] = mlx_load_xpm42("textures/gameover.xpm42");
	else
		data->xpm[SCREEN] = mlx_load_xpm42("textures/youwon.xpm42");
	data->img[SCREEN] = mlx_texture_to_image(data->mlx, \
							&data->xpm[SCREEN]->texture);
	if (mlx_image_to_window(data->mlx, data->img[SCREEN], \
										display_x, display_y) == -1)
		(free_close_window(data, data->img[SCREEN], "image_to_window failed"));
	if (death == true)
		mlx_put_string(data->mlx, "Press any key to continue...", \
									display_x + 70, display_y + 200);
	else
		mlx_put_string(data->mlx, "Press any key to continue...", \
										display_x, display_y + 100);
	usleep(10);
}

/**
 * Converts a counter from an integer to a string, then combines it with the 
 * string provided as parameter and then puts that string to the screen.
 * Setting the instance depth because every time a new image is displayed,
 * the instance depth iterates and it cannot do so ad infinitum.
 * Also cannot use ft_itoa and strjoin at the same time bc memory leaks. 
 * data->count[str_img]    - counter in integers      	 -  int     2
 * data->str[str_img]      - integer in string form   	 -  char * "2"
 * data->combstr[str_img]  - combined with text,   		 -  char * "lives: 2"
 * data->img[str_img] 	   - image pointer to the string -  mlx_image_t *
 */
void	display_string(t_imgdata *data, int32_t str_img, size_t x, char *str)
{
	if (data->img[str_img])
		mlx_delete_image(data->mlx, data->img[str_img]);
	data->str[str_img] = ft_itoa(data->count[str_img]);
	if (!(data->str[str_img]))
		return (free_close_window(data, data->str, \
									"Error\nFailed string"));
	data->combstr[str_img] = ft_strjoin(str, data->str[str_img]);
	if (!(data->combstr[str_img]))
		return (free_close_window(data, data->combstr, \
									"Error\nFailed string"));
	free(data->str[str_img]);
	data->img[str_img] = mlx_put_string(data->mlx, \
								data->combstr[str_img], x, 0);
	free(data->combstr[str_img]);
	mlx_set_instance_depth(data->img[str_img]->instances, 200);
}
