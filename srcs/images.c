/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:40:13 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/22 23:49:53 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	windowdisplay(t_imgdata *data, t_line *line)
{
	data->width = line->size * BLOK;
	data->height = (line->count * (BLOK)) + BLOK;
	if (data->width > 1920 || data->height > 960)
		return (ft_putendl_fd("Map is too big", STDOUT_FILENO), false);
	else if (data->width <= 1920 && data->width > 1536)
		data->xpm[BG] = mlx_load_xpm42("textures/bg_1920.xpm42");
	else if (data->width <= 1536 && data->width > 1280)
		data->xpm[BG] = mlx_load_xpm42("textures/bg_1536.xpm42");
	else if (data->width <= 1280 && data->width > 960)
		data->xpm[BG] = mlx_load_xpm42("textures/bg_1280.xpm42");
	else if (data->width <= 960 && data->width > 640)
		data->xpm[BG] = mlx_load_xpm42("textures/bg_960.xpm42");
	else if (data->width <= 640 && data->width > 313)
		data->xpm[BG] = mlx_load_xpm42("textures/bg_640.xpm42");
	else if (data->width <= 313)
		data->xpm[BG] = mlx_load_xpm42("textures/bg_313.xpm42");
	if (!data->xpm[BG])
		return (ft_putendl_fd("bg was not found", STDOUT_FILENO), false);
	data->mlx = mlx_init(data->width, data->height, "yoooo", true);
	if (!data->mlx)
		return (false);
	return (true);
}

bool	loading_images(t_imgdata *data, xpm_t **xpm)
{
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
	data->ghost = mlx_load_png("textures/ghost_trans2.png");
	if (!data->ghost)
		return (ft_putendl_fd("ghost was not found", STDOUT_FILENO), false);
	return (true);
}

void	texture_to_image(t_imgdata *data, xpm_t **xpm)
{
	const uint32_t		xy[] = {60, 40};
	const uint32_t		wh2[] = {32, 32};

	data->img[BG] = mlx_texture_to_image(data->mlx, &xpm[BG]->texture);
	data->img[CHAR] = mlx_texture_area_to_image(data->mlx, \
						&xpm[CHAR]->texture, (uint32_t *)xy, (uint32_t *)wh2);
	data->img[TILE] = mlx_texture_to_image(data->mlx, &xpm[TILE]->texture);
	data->img[WALL] = mlx_texture_to_image(data->mlx, &xpm[WALL]->texture);
	data->img[PICKUP] = mlx_texture_to_image(data->mlx, &xpm[PICKUP]->texture);
	data->img[DOOR] = mlx_texture_to_image(data->mlx, &xpm[DOOR]->texture);
	data->img[GHOST] = mlx_texture_to_image(data->mlx, data->ghost);
}

void	images_to_window(t_imgdata *data, mlx_image_t **img, \
						t_line *line, size_t i)
{
	size_t	x;
	size_t	y;
	size_t	j;

	j = 0;
	while (data->bigass[i])
	{
		x = i % (data->line.size + 1);
		y = i / (data->line.size + 1);
		if (data->bigass[i] == '1')
		{
			if (x == 0 || y == 0 || y == line->count || x == line->size - 1)
				mlx_image_to_window(data->mlx, img[WALL], x * BLOK, y * BLOK);
			else
				mlx_image_to_window(data->mlx, img[TILE], x * BLOK, y * BLOK);
		}
		else if (data->bigass[i] == 'C')
			mlx_image_to_window(data->mlx, img[PICKUP], x * BLOK, y * BLOK);
		else if (data->bigass[i] == 'P')
			mlx_image_to_window(data->mlx, img[CHAR], x * BLOK, y * BLOK);
		else if (data->map[y][x] == 'E')
			mlx_image_to_window(data->mlx, img[DOOR], x * BLOK, y * BLOK);
		enemy_to_window(data, &x, &y);
		i++;
	}
}
