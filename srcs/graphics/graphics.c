/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/18 02:15:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_data(t_imgdata *data)
{
	obstacle_pickup(data);
	data->accel = ACCEL;
	data->old_x = (data->img[CHAR_R]->instances[0].x);
	data->old_y = (data->img[CHAR_R]->instances[0].y);
}

static bool	init_graphics(t_imgdata *data, t_line *line)
{
	if (!(windowdisplay(data, line, data->xpm)) || !(loading_images(data, \
	data->xpm)) || !(texture_to_image(data, data->xpm, data->img)) || \
	!(images_to_window(data, 0)))
		return (false);
	if (mlx_image_to_window(data->mlx, data->img[BG], 0, 0) == -1)
		return (free_close_window(data, data->img[BG], \
						"image_to_window failed"), false);
	mlx_set_instance_depth(data->img[BG]->instances, -999);
	return (true);
}

/**
 * A hook allows a function to be executed every frame of the game loop,
 * executed by the graphical library. I am seperating certain conditions
 * from the rest of the game to make sure the game freezes at end conditions:
 * having collected all collectibles and exiting or having lost all lives.
 */
static void	hook(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				x;
	size_t				y;

	x = (data2->img[CHAR_R]->instances[0].x / BLOK);
	y = (data2->img[CHAR_R]->instances[0].y / BLOK);
	if ((data2->map[y][x] == 'E' && data2->pickup_count >= data2->pickup_max))
		terminate(data);
	else
	{
		if (mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
			terminate(data);
		gravity(data2, x, y);
		movement(data2, x, y);
		x = (data2->img[CHAR_R]->instances[0].x);
		y = (data2->img[CHAR_R]->instances[0].y);
		collect(data2, x, y);
		movecounter(data2, x, y);
		data2->count[FRAME]++;
	}
}

/**
 * I am forking because otherwise the background music takes over the process
 * of the game. If I wanted to use sounds while the game runs, I would need
 * threads. If the game loop is running in two processes, OpenGL complains. 
 */
int32_t	graphics(t_imgdata *data, t_line *line)
{
	if (!init_graphics(data, line))
		return (false);
	init_data(data);
	if (!(mlx_loop_hook(data->mlx, &hook, data)))
		(error_close_window(data, "loop hook failed"));
	mlx_loop(data->mlx);
	if (data->bigass)
		free (data->bigass);
	return (0);
}
