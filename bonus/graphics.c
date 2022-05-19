/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/19 19:37:17 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * Initialising certain variables before the game loop starts
 * because if you initialise things in the loop, it will reset
 * to said value every frame.
 */
static void	init(t_imgdata *data)
{
	data->count[LIFE] = LIVES;
	data->accel = ACCEL;
	data->enemy.time_lock = false;
	data->old_x = (data->img[CHAR]->instances[0].x);
	data->old_y = (data->img[CHAR]->instances[0].y);
	data->animate.xy[0] = 60;
	data->animate.dir = CHAR;
	data->total_enemies = PINKCOUNT + GHOSTCOUNT;
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

	x = (data2->img[CHAR]->instances[0].x / BLOK);
	y = (data2->img[CHAR]->instances[0].y / BLOK);
	if (data2->count[LIFE] <= 0 || \
		(data2->map[y][x] == 'E' && data2->collect == 0))
		end_message(data2);
	else
	{
		if (mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
			terminate(data);
		movement(data2, x, y);
		collect(data2, x, y);
		gravity(data2, x, y);
		enemies(data2, &data2->enemy, x, y);
		x = (data2->img[CHAR]->instances[0].x);
		y = (data2->img[CHAR]->instances[0].y);
		animate_char(data2, &data2->animate, x, y);
		movecounter(data2, &data2->animate, x, y);
		display_string(data2, STRMOVE, 10, "movement: ");
		display_string(data2, STRLIFE, 200, "lives: ");
	}
}

/**
 * I am forking because otherwise the background music takes over the process
 * of the game. If I wanted to use sounds while the game runs, I would need
 * threads. If the game loop is running in two processes, OpenGL complains. 
 */
int32_t	graphics(t_imgdata *data, t_line *line, t_enemy *enemy)
{
	const char	*args[] = {"/usr/bin/afplay", "--volume", "0", \
	"/Users/mialbert/Documents/test/audio/scape.mp3", NULL};

	if (!(windowdisplay(data, line, data->xpm)) || !(loading_images(data, \
	data->xpm)) || !(texture_to_image(data, data->xpm, data->img)) || \
	!(images_to_window(data, 0)) || !(enemy_to_window(data, enemy->ghost_spawn, \
	GHOSTCOUNT, enemy->ghost_img)) || enemy_to_window(data, enemy->pink_spawn, \
	PINKCOUNT, enemy->ghost_img))
		return (0);
	if (mlx_image_to_window(data->mlx, data->img[BG], 0, 0) == -1)
		return (free_close_window(data, data->img[BG], \
						"image_to_window failed"), 0);
	mlx_set_instance_depth(data->img[BG]->instances, -999);
	init(data);
	data->pid = fork();
	if (data->pid == 0)
		execvp(args[0], (char **)args);
	else
	{
		if (!(mlx_loop_hook(data->mlx, &hook, data)))
			(error_close_window(data, "loop hook failed"));
		mlx_loop(data->mlx);
	}
	if (data->bigass)
		free (data->bigass);
	return (0);
}
