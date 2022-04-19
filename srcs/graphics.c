/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/19 17:45:00 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"

static bool	loading_images(t_imgdata *data, xpm_t **xpm)
{
	uint32_t		xy[] = {60, 40};
	uint32_t		wh2[] = {32, 32};

	xpm[BG] = mlx_load_xpm42("textures/merged.xpm42");
	if (!xpm[BG])
		return (ft_putendl_fd("bg was not found", STDOUT_FILENO), false);
	xpm[TILE] = mlx_load_xpm42("textures/tile.xpm42");
	if (!xpm[TILE])
		return (ft_putendl_fd("tile was not found", STDOUT_FILENO), false);
	xpm[WALL] = mlx_load_xpm42("textures/wall.xpm42");
	if (!xpm[WALL])
		return (ft_putendl_fd("wall was not found", STDOUT_FILENO), false);
	xpm[PICKUP] = mlx_load_xpm42("textures/pickup32.xpm42");
	if (!xpm[PICKUP])
		return (ft_putendl_fd("pickup was not found", STDOUT_FILENO), false);
	xpm[DOOR] = mlx_load_xpm42("textures/doortrans.xpm42");
	if (!xpm[DOOR])
		return (ft_putendl_fd("door was not found", STDOUT_FILENO), false);
	xpm[CHAR] = mlx_load_xpm42("textures/main.xpm42");
	if (!xpm[CHAR])
		return (ft_putendl_fd("char was not found", STDOUT_FILENO), false);
	xpm[GHOST] = mlx_load_xpm42("textures/ghost.xpm42");
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

// static void	physics(void *data)
// {
// 	t_imgdata *const	data2 = data;
// 	int32_t				x;
// 	int32_t				y;
// 	size_t				i;

// 	i = 0;
// 	x = (data2->character->instances[0].x / data2->blok);
// 	y = (data2->character->instances[0].y / data2->blok);
// 	if (data2->map[y - 1][x] != '1')
// 		data2->character->instances[0].y += data2->blok;
// }

// static void	pickups(void *data)
// {
// 	t_imgdata *const	data2 = data;
// 	int32_t				x;
// 	int32_t				y;
// 	size_t				i;

// 	i = 0;
// 	x = (data2->character->instances[0].x / data2->blok);
// 	y = (data2->character->instances[0].y / data2->blok);
// 	if (data2->map[y][x] == 'C')
// 	{
// 		data2->map[y][x] = '0';
// 		mlx_image_to_window(data2->mlx, data2->bg, 0, 0);
// 		data2->collect--;
// 	}
// 	if (data2->map[y][x] == 'E' && data2->collect == 0)
// 		mlx_close_window(data2->mlx);
// }

static void	hooks(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				x;
	size_t				y;
	size_t				i;
	size_t				jump;
	float				vel;

	i = 0;
	vel = 50;
	jump = 0;
	x = (data2->img[CHAR]->instances[0].x / data2->blok);
	y = (data2->img[CHAR]->instances[0].y / data2->blok);
	// data2->movestr = gnl_strjoin("movement: ", ft_itoa(data2->movecount));
	// mlx_put_string(data2->mlx, data2->movestr, 10, 0);
	// free (data2->movestr);
	// printf("%s", ft_strjoin("movement: ", ft_itoa(data2->movecount)));
	if (data2->map[y + 1][x] != '1')
		data2->img[CHAR]->instances[0].y += 3;
	if (data2->map[y][x] == 'C')
	{
		i = find_instance((t_imgdata *)data2, x, y);
		data2->map[y][x] = 'K';
		mlx_set_instance_depth(&data2->img[PICKUP]->instances[i], -1);
		data2->collect--;
	}
	if (data2->map[y][x] == 'E' && data2->collect == 0)
		mlx_close_window(data2->mlx);
	if (mlx_is_key_down(data2->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data2->mlx);
	if (mlx_is_key_down(data2->mlx, MLX_KEY_S) || mlx_is_key_down \
		(data2->mlx, MLX_KEY_D) || mlx_is_key_down \
		(data2->mlx, MLX_KEY_A) || mlx_is_key_down(data2->mlx, MLX_KEY_W))
	{	
		data2->movecount++;
		if (mlx_is_key_down(data2->mlx, MLX_KEY_S) \
							&& data2->map[y + 1][x] != '1')
				data2->img[CHAR]->instances[0].y += data2->blok / 3;
		else if (mlx_is_key_down(data2->mlx, MLX_KEY_W) \
								&& data2->map[y - 1][x] != '1' && y - 1 != 0)
			data2->img[CHAR]->instances[0].y -= data2->blok / 2;
		else if (mlx_is_key_down(data2->mlx, MLX_KEY_A) \
								&& data2->map[y][x - 1] != '1')
			data2->img[CHAR]->instances[0].x -= data2->blok / 3;
		else if (mlx_is_key_down(data2->mlx, MLX_KEY_D) \
								&& data2->map[y][x + 1] != '1')
			data2->img[CHAR]->instances[0].x += data2->blok / 3;
	}
}

int32_t	graphics(t_imgdata *data, t_line *line)
{
	int32_t			colour;
	int32_t			i;

	i = 0;
	colour = 0;
	data->blok = 32;
	data->width = line->size * data->blok;
	if (data->width > 960)
		data->width = 960;
	data->height = (line->count * (data->blok)) + data->blok;
	if (data->height > 475)
		data->height = 475;
	data->mlx = mlx_init(data->width, data->height, "yoooo", true);
	if (!data->mlx)
		return (0);
	if (!loading_images(data, data->xpm))
		return (0);
	mlx_image_to_window(data->mlx, data->img[BG], 0, 0);
	images_to_window(data, data->img, line, data->blok);
	mlx_loop_hook(data->mlx, &hooks, data);
	// mlx_loop_hook(data->mlx, &physics, data);
	// mlx_loop_hook(data->mlx, &pickups, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
