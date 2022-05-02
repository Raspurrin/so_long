/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/01 19:53:24 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init(t_imgdata *data)
{
	data->count[LIFE] = LIVES;
	data->accel = ACCEL;
	data->enemy.time_lock = false;
	data->old_x = (data->img[CHAR]->instances[0].x / BLOK);
	data->old_y = (data->img[CHAR]->instances[0].y / BLOK);
}

static void	hook(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				x;
	size_t				y;

	x = (data2->img[CHAR]->instances[0].x / BLOK);
	y = (data2->img[CHAR]->instances[0].y / BLOK);
	movement(data2, x, y);
	movecounter(data2, x, y);
	display_string(data2, MOVE, 10, "movement: ");
	display_string(data2, LIFE, 200, "lives: ");
	collect(data2, x, y);
	// enemies(data2, &data2->enemy, x, y);
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
	if (!(windowdisplay(data, line)) || !(loading_images(data, data->xpm)) || \
		!(texture_to_image(data, data->xpm)) || \
		!(images_to_window(data, data->img, 0)) || \
		!(enemy_to_window(data)))
		return (0);
	init(data);
	data->pid = fork();
	if (data->pid == 0)
		system("afplay --volume 0 \
				/Users/mialbert/Documents/test/audio/scape.mp3");
	else
	{
		if (!(mlx_loop_hook(data->mlx, &hook, data)))
			(error_close_window(data, "loop hook failed"));
		mlx_loop(data->mlx);
		mlx_delete_image(data->mlx, data->img[GREY]);
		mlx_delete_image(data->mlx, data->img[SCREEN]);
		mlx_terminate(data->mlx);
	}
	return (0);
}
