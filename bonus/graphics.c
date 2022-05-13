/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/14 00:00:22 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init(t_imgdata *data)
{
	data->count[LIFE] = LIVES;
	data->accel = ACCEL;
	data->enemy.time_lock = false;
	data->old_x = (data->img[CHAR]->instances[0].x);
	data->old_y = (data->img[CHAR]->instances[0].y);
	data->animate.xy[0] = 60;
}

static void	end_message(t_imgdata *data)
{
	if (data->count[LIFE] <= 0)
		display_message(data, true, 3.5, 3);
	else
		display_message(data, false, 3, 3);
	mlx_key_hook(data->mlx, &end, data);
}

static void	hook(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				x;
	size_t				y;

	x = (data2->img[CHAR]->instances[0].x / BLOK);
	y = (data2->img[CHAR]->instances[0].y / BLOK);
	if (data2->count[LIFE] <= 0 || \
		(data2->map[y][x] == 'E' && data2->collect == 0))
		end_message(data2);
	else
	{
		movement(data2, x, y);
		collect(data2, x, y);
		gravity(data2, x, y);
		enemies(data2, &data2->enemy, x, y);
		x = (data2->img[CHAR]->instances[0].x);
		y = (data2->img[CHAR]->instances[0].y);
		movecounter(data2, &data2->animate, x, y);
		display_string(data2, STRMOVE, 10, "movement: ");
		display_string(data2, STRLIFE, 200, "lives: ");
		animation(data2, &data2->animate, x, y);
	}
}

int32_t	graphics(t_imgdata *data, t_line *line)
{
	char	*args[] = {"/usr/bin/afplay", "--volume", "1", \
			"/Users/mialbert/Documents/test/audio/scape.mp3", NULL};

	if (!(windowdisplay(data, line)) || !(loading_images(data, data->xpm)) || \
		!(texture_to_image(data, data->xpm)) || \
		!(images_to_window(data, 0)) || \
		!(enemy_to_window(data, &data->enemy)))
		return (0);
	if (mlx_image_to_window(data->mlx, data->img[BG], 0, 0) == -1)
		return (free_close_window(data, data->img[BG], \
						"image_to_window failed"), 0);
	mlx_set_instance_depth(data->img[BG]->instances, -999);
	init(data);
	data->pid = fork();
	if (data->pid == 0)
		execvp(args[0], args);
	else
	{
		if (!(mlx_loop_hook(data->mlx, &hook, data)))
			(error_close_window(data, "loop hook failed"));
		mlx_loop(data->mlx);
		mlx_delete_image(data->mlx, data->img[GREY]);
		mlx_delete_image(data->mlx, data->img[SCREEN]);
		mlx_terminate(data->mlx);
	}
	// free(data->bigass);
	return (0);
}
