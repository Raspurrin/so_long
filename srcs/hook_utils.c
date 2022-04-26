/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:06:05 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/26 22:46:09 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	movement(t_imgdata *data, size_t x, size_t y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) \
						&& data->map[y + 1][x] != '1')
			data->img[CHAR]->instances[0].y += BLOK / 3;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A) \
							&& data->map[y][x - 1] != '1')
		data->img[CHAR]->instances[0].x -= BLOK / 3;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) \
							&& data->map[y][x + 1] != '1')
		data->img[CHAR]->instances[0].x += BLOK / 3;
}

void	movecounter(t_imgdata *data, size_t x, size_t y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down \
		(data->mlx, MLX_KEY_D) || mlx_is_key_down \
		(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx, MLX_KEY_W))
	{	
		if (x == data->old_x + 1 || x == data->old_x - 1 \
			|| y == data->old_y + 1 || y == data->old_y - 1)
		{
			data->old_x = x;
			data->old_y = y;
			data->count[MOVE]++;
		}
	}
}

void	display_string(t_imgdata *data, int32_t str_img, size_t x, char *str)
{
	if (data->img[str_img])
		mlx_delete_image(data->mlx, data->img[str_img]);
	data->str[str_img] = ft_itoa(data->count[str_img]);
	data->combstr[str_img] = ft_strjoin(str, data->str[str_img]);
	data->img[str_img] = mlx_put_string(data->mlx, \
								data->combstr[str_img], x, 0);
}

void	end(mlx_key_data_t keydata, void *data)
{
	t_imgdata *const	data2 = data;

	if (mlx_is_key_down(data2->mlx, keydata.key))
		mlx_close_window(data2->mlx);
}

void	collect(t_imgdata *data, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	if (data->map[y][x] == 'C')
	{
		i = find_c_instance((t_imgdata *)data, x, y);
		data->map[y][x] = 'K';
		mlx_set_instance_depth(&data->img[PICKUP]->instances[i], -1);
		data->collect--;
	}
	if ((data->map[y][x] == 'E' && data->collect == 0))
	{
		display_message(data, false, 3, 3);
		mlx_key_hook(data->mlx, &end, data);
	}
}
