/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/23 02:25:48 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"
#include <signal.h>

static void	char_move(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				x;
	size_t				y;

	x = (data2->img[CHAR]->instances[0].x / BLOK);
	y = (data2->img[CHAR]->instances[0].y / BLOK);
	if (mlx_is_key_down(data2->mlx, MLX_KEY_S) || mlx_is_key_down \
		(data2->mlx, MLX_KEY_D) || mlx_is_key_down \
		(data2->mlx, MLX_KEY_A) || mlx_is_key_down(data2->mlx, MLX_KEY_W))
	{	
		data2->movecount++;
		if (mlx_is_key_down(data2->mlx, MLX_KEY_S) \
							&& data2->map[y + 1][x] != '1')
				data2->img[CHAR]->instances[0].y += BLOK / 3;
		else if (mlx_is_key_down(data2->mlx, MLX_KEY_W) \
								&& data2->map[y - 1][x] != '1' && y - 1 != 0)
			data2->img[CHAR]->instances[0].y -= BLOK / 3;
		else if (mlx_is_key_down(data2->mlx, MLX_KEY_A) \
								&& data2->map[y][x - 1] != '1')
			data2->img[CHAR]->instances[0].x -= BLOK / 3;
		else if (mlx_is_key_down(data2->mlx, MLX_KEY_D) \
								&& data2->map[y][x + 1] != '1')
			data2->img[CHAR]->instances[0].x += BLOK / 3;
	}
}

static void	end(mlx_key_data_t keydata, void *data)
{
	t_imgdata *const	data2 = data;

	mlx_close_window(data2->mlx);
}

static void	utils(void	*data)
{
	t_imgdata *const	data2 = data;
	char				*movecount;
	size_t				x;
	size_t				y;
	size_t				i;

	i = 0;
	x = (data2->img[CHAR]->instances[0].x / BLOK);
	y = (data2->img[CHAR]->instances[0].y / BLOK);
	if (data2->map[y + 1][x] != '1')
		data2->img[CHAR]->instances[0].y += 3;
	mlx_delete_image(data2->mlx, data2->img[STR]);
	movecount = ft_itoa(data2->movecount);
	data2->movestr = ft_strjoin("movement: ", movecount);
	data2->img[STR] = mlx_put_string(data2->mlx, data2->movestr, 10, 0);
	free (data2->movestr);
	if (data2->map[y][x] == 'C')
	{
		i = find_c_instance((t_imgdata *)data2, x, y);
		data2->map[y][x] = 'K';
		mlx_set_instance_depth(&data2->img[PICKUP]->instances[i], -1);
		data2->collect--;
	}
	if ((data2->map[y][x] == 'E' && data2->collect == 0))
	{
		display_message(data2, false);
		// mlx_key_hook(data2->mlx, &end, data2);
	}
}



static void	death(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				player[2];
	size_t				i;
	size_t				x;
	size_t				y;

	i = 0;
	player[X] = (data2->img[CHAR]->instances[0].x / BLOK);
	player[Y] = (data2->img[CHAR]->instances[0].y / BLOK);
	while (i < ENEMYCOUNT)
	{
		x = (data2->img[GHOST]->instances[i].x / BLOK);
		y = (data2->img[GHOST]->instances[i].y / BLOK);
		if ((player[X] == x && player[Y] == y) || \
		mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
		{
			if (player[X] == x && player[Y] == y)
				data2->lives--;
		}
		if (data2->lives == 0)
			display_message(data2, true);
		i++;
	}
	if (mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data2->mlx);
}

int32_t	graphics(t_imgdata *data, t_line *line)
{
	if (!(windowdisplay(data, line)) || !(loading_images(data, data->xpm)))
		return (0);
	texture_to_image(data, data->xpm);
	mlx_image_to_window(data->mlx, data->img[BG], 0, 0);
	images_to_window(data, data->img, line, 0);
	data->pid = fork();
	// if (data->pid == 0)
	// 	system("afplay --volume 0 \
	// 			/Users/mialbert/Documents/test/audio/scape.mp3");
	// else
	// {
	mlx_loop_hook(data->mlx, &char_move, data);
	mlx_loop_hook(data->mlx, &enemy_move, data);
	mlx_loop_hook(data->mlx, &utils, data);
	mlx_loop_hook(data->mlx, &death, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img[GREY]);
	mlx_delete_image(data->mlx, data->img[SCREEN]);
	mlx_terminate(data->mlx);
	kill(0, SIGKILL);
	// }
	return (0);
}
