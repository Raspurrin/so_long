/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/20 23:17:15 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"
#include <signal.h>

static bool	loading_images(t_imgdata *data, xpm_t **xpm)
{
	uint32_t		xy[] = {60, 40};
	uint32_t		wh2[] = {32, 32};

	xpm[BG] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/merged.xpm42");
	if (!xpm[BG])
		return (ft_putendl_fd("bg was not found", STDOUT_FILENO), false);
	xpm[TILE] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/tile.xpm42");
	if (!xpm[TILE])
		return (ft_putendl_fd("tile was not found", STDOUT_FILENO), false);
	xpm[WALL] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/wall.xpm42");
	if (!xpm[WALL])
		return (ft_putendl_fd("wall was not found", STDOUT_FILENO), false);
	xpm[PICKUP] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/pickup32.xpm42");
	if (!xpm[PICKUP])
		return (ft_putendl_fd("pickup was not found", STDOUT_FILENO), false);
	xpm[DOOR] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/doortrans.xpm42");
	if (!xpm[DOOR])
		return (ft_putendl_fd("door was not found", STDOUT_FILENO), false);
	xpm[CHAR] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/main.xpm42");
	if (!xpm[CHAR])
		return (ft_putendl_fd("char was not found", STDOUT_FILENO), false);
	xpm[GHOST] = mlx_load_xpm42("/Users/mialbert/Documents/test/textures/ghost.xpm42");
	if (!xpm[GHOST])
		return (ft_putendl_fd("ghost was not found", STDOUT_FILENO), false);
	data->img[BG] = mlx_texture_to_image(data->mlx, &xpm[BG]->texture);
	data->img[CHAR] = mlx_texture_area_to_image(data->mlx, \
											&xpm[CHAR]->texture, xy, wh2);
	data->img[TILE] = mlx_texture_to_image(data->mlx, &xpm[TILE]->texture);
	data->img[WALL] = mlx_texture_to_image(data->mlx, &xpm[WALL]->texture);
	data->img[PICKUP] = mlx_texture_to_image(data->mlx, &xpm[PICKUP]->texture);
	data->img[DOOR] = mlx_texture_to_image(data->mlx, &xpm[DOOR]->texture);
	data->img[GHOST] = mlx_texture_to_image(data->mlx, &xpm[GHOST]->texture);
	return (true);
}

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
	movecount = ft_itoa(data2->movecount);
	data2->movestr = ft_strjoin("movement: ", movecount);
	mlx_put_string(data2->mlx, data2->movestr, 10, 0);
	free (data2->movestr);
	if (mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data2->mlx);
	if (data2->map[y][x] == 'C')
	{
		i = find_instance((t_imgdata *)data2, x, y);
		data2->map[y][x] = 'K';
		mlx_set_instance_depth(&data2->img[PICKUP]->instances[i], -1);
		data2->collect--;
	}
	if (data2->map[y][x] == 'E' && data2->collect == 0)
		mlx_close_window(data2->mlx);
}

static void	enemy_move(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				i;
	size_t				x;
	size_t				y;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		x = (data2->img[GHOST]->instances[1].x / BLOK);
		y = (data2->img[GHOST]->instances[1].y / BLOK);
		data2->move[i] = rand() % ENEMYCOUNT + 1;
		if (data2->move[i] == 1 \
							&& data2->map[y + 1][x] != '1')
				data2->img[GHOST]->instances[i].y += BLOK / 8;
		else if (data2->move[i] == 2 \
								&& data2->map[y - 1][x] != '1' && y - 1 != 0)
			data2->img[GHOST]->instances[i].y -= BLOK / 8;
		else if (data2->move[i] == 3 \
								&& data2->map[y][x - 1] != '1')
			data2->img[GHOST]->instances[i].x -= BLOK / 8;
		else if (data2->move[i] == 4 \
								&& data2->map[y][x + 1] != '1')
			data2->img[GHOST]->instances[i].x += BLOK / 8;
		i++;
	}
}

static void	death(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				player[XY];
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
		if (player[X] == x && player[Y] == y)
		{
				kill(data2->test, SIGKILL);
				mlx_close_window(data2->mlx);
		}
		i++;
	}
}

int32_t	graphics(t_imgdata *data, t_line *line)
{
	int32_t			colour;
	int32_t			i;

	i = 0;
	colour = 0;
	data->width = line->size * BLOK;
	if (data->width > 960)
		data->width = 960;
	data->height = (line->count * (BLOK)) + BLOK;
	if (data->height > 475)
		data->height = 475;
	data->mlx = mlx_init(data->width, data->height, "yoooo", true);
	if (!data->mlx)
		return (0);
	if (!loading_images(data, data->xpm))
		return (0);
	mlx_image_to_window(data->mlx, data->img[BG], 0, 0);
	images_to_window(data, data->img, line, BLOK);
	data->test = fork();
	// sigaction(data->test, )
	if (data->test == 0)
		system("afplay --volume 1 /Users/mialbert/Documents/test/audio/scape.mp3");
	else
	{
		mlx_loop_hook(data->mlx, &char_move, data);
		mlx_loop_hook(data->mlx, &enemy_move, data);
		mlx_loop_hook(data->mlx, &utils, data);
		mlx_loop_hook(data->mlx, &death, data);
		mlx_loop(data->mlx);
		mlx_terminate(data->mlx);
	}
	return (0);
}
