/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 23:51:24 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/29 03:26:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
