/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/28 00:49:40 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <signal.h>

static void	hook(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				x;
	size_t				y;

	x = (data2->img[CHAR]->instances[0].x / BLOK);
	y = (data2->img[CHAR]->instances[0].y / BLOK);
	movement(data2, x, y);
	data2->current_time = mlx_get_time();
	if (data2->time_lock == true && \
		data2->current_time == (data2->enemy_time + 2))
		data2->time_lock = false;
	movecounter(data2, x, y);
	display_string(data2, MOVE, 10, "movement: ");
	display_string(data2, LIFE, 200, "lives: ");
	collect(data2, x, y);
	enemies(data2, x, y);
	gravity(data2, x, y);
	x = (data2->img[CHAR]->instances[0].x);
	y = (data2->img[CHAR]->instances[0].y);
	animation(data2, x, y);
	if (mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data2->mlx);
		kill(0, SIGKILL);
	}
}

int32_t	graphics(t_imgdata *data, t_line *line)
{
	if (!(windowdisplay(data, line)) || !(loading_images(data, data->xpm)))
		return (0);
	texture_to_image(data, data->xpm);
	mlx_image_to_window(data->mlx, data->img[BG], 0, 0);
	images_to_window(data, data->img, line, 0);
	data->count[LIFE] = LIVES;
	data->accel = ACCEL;
	data->time_lock = false;
	data->old_x = (data->img[CHAR]->instances[0].x / BLOK);
	data->old_y = (data->img[CHAR]->instances[0].y / BLOK);
	data->pid = fork();
	if (data->pid == 0)
		system("afplay --volume 0 \
				/Users/mialbert/Documents/test/audio/scape.mp3");
	else
	{
		mlx_loop_hook(data->mlx, &hook, data);
		mlx_loop(data->mlx);
		mlx_delete_image(data->mlx, data->img[GREY]);
		mlx_delete_image(data->mlx, data->img[SCREEN]);
		mlx_terminate(data->mlx);
	}
	return (0);
}
