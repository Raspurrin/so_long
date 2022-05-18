/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:40:13 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/18 02:28:23 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * Loads different sized background images based on the size of the map
 */
bool	windowdisplay(t_imgdata *data, t_line *line, xpm_t **xpm)
{
	data->width = line->size * BLOK;
	data->height = (line->count * (BLOK)) + BLOK;
	if (data->width > 1920 || data->height > 960)
		return (ft_putendl_fd("Map is too big", STDOUT_FILENO), false);
	else if (data->width <= 1920 && data->width > 1536)
		xpm[BG] = mlx_load_xpm42("textures/bg_1920.xpm42");
	else if (data->width <= 1536 && data->width > 1280)
		xpm[BG] = mlx_load_xpm42("textures/bg_1536.xpm42");
	else if (data->width <= 1280 && data->width > 960)
		xpm[BG] = mlx_load_xpm42("textures/bg_1280.xpm42");
	else if (data->width <= 960 && data->width > 640)
		xpm[BG] = mlx_load_xpm42("textures/bg_960.xpm42");
	else if (data->width <= 640 && data->width > 313)
		xpm[BG] = mlx_load_xpm42("textures/bg_640.xpm42");
	else if (data->width <= 313)
		xpm[BG] = mlx_load_xpm42("textures/bg_313.xpm42");
	if (!xpm[BG])
		return (ft_putendl_fd("bg was not found", STDOUT_FILENO), false);
	return (true);
}

static bool	loading_images2(t_imgdata *data, xpm_t **xpm)
{
	xpm[CHAR] = mlx_load_xpm42("textures/main.xpm42");
	if (!xpm[CHAR])
		return (ft_putendl_fd("char was not found", STDOUT_FILENO), false);
	xpm[CHAR_L] = mlx_load_xpm42("textures/main_rev.xpm42");
	if (!xpm[CHAR_L])
		return (ft_putendl_fd("char_l was not found", STDOUT_FILENO), false);
	data->enemy.ghost = mlx_load_png("textures/ghost_trans2.png");
	if (!data->enemy.ghost)
		return (ft_putendl_fd("ghost was not found", STDOUT_FILENO), false);
	data->enemy.ghost_r = mlx_load_png("textures/ghost_right.png");
	if (!data->enemy.ghost_r)
		return (ft_putendl_fd("ghost_r not found", STDOUT_FILENO), false);
	return (true);
}

bool	loading_images(t_imgdata *data, xpm_t **xpm)
{
	data->mlx = mlx_init(data->width, data->height, "Waste of time", true);
	if (!data->mlx)
		return (0);
	xpm[TILE] = mlx_load_xpm42("textures/tile.xpm42");
	if (!xpm[TILE])
		return (ft_putendl_fd("tile was not found", STDOUT_FILENO), false);
	xpm[WALL] = mlx_load_xpm42("textures/wall.xpm42");
	if (!xpm[WALL])
		return (ft_putendl_fd("wall was not found", STDOUT_FILENO), false);
	xpm[PICKUP] = mlx_load_xpm42("textures/pickup32.xpm42");
	if (!xpm[PICKUP])
		return (ft_putendl_fd("pickup was not found", STDOUT_FILENO), false);
	xpm[DOOR] = mlx_load_xpm42("textures/doortrans2.xpm42");
	if (!xpm[DOOR])
		return (ft_putendl_fd("door was not found", STDOUT_FILENO), false);
	if (!loading_images2(data, xpm))
		return (false);
	return (true);
}

bool	texture_to_image(t_imgdata *data, xpm_t **xpm, mlx_image_t **img)
{
	const uint32_t		wh2[] = {32, 32};
	size_t				i;		

	i = 0;
	data->xy[0] = 60;
	data->xy[1] = 40;
	data->char_start = data->xy[0];
	img[BG] = mlx_texture_to_image(data->mlx, &xpm[BG]->texture);
	img[CHAR] = mlx_texture_area_to_image(data->mlx, \
						&xpm[CHAR]->texture, data->xy, (uint32_t *)wh2);
	img[TILE] = mlx_texture_to_image(data->mlx, &xpm[TILE]->texture);
	img[WALL] = mlx_texture_to_image(data->mlx, &xpm[WALL]->texture);
	img[PICKUP] = mlx_texture_to_image(data->mlx, &xpm[PICKUP]->texture);
	img[DOOR] = mlx_texture_to_image(data->mlx, &xpm[DOOR]->texture);
	while (i < GHOSTCOUNT)
	{
		data->enemy.img[i] = mlx_texture_to_image(data->mlx, data->enemy.ghost);
		if (!data->enemy.img[i++])
			return (ft_putendl_fd("Texture failed", STDOUT_FILENO), false);
	}
	if (!img[BG] || !img[CHAR] || !img[TILE] || !img[WALL] || !img[PICKUP] \
		|| !img[DOOR])
		return (ft_putendl_fd("Texture to image failed", STDOUT_FILENO), false);
	return (true);
}
