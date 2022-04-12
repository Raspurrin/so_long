/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/12 19:50:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"

static bool	loading_images(t_imgdata *data)
{
	uint32_t		xy[] = {50, 50};
	uint32_t		wh2[] = {50, 30};

	data->xpm_bg = mlx_load_xpm42("textures/merged.xpm42");
	if (!data->xpm_bg)
		return (ft_putendl_fd("bg was not found", STDOUT_FILENO), false);
	data->xpm_char = mlx_load_xpm42("textures/main.xpm42");
	if (!data->xpm_char)
		return (ft_putendl_fd("char was not found", STDOUT_FILENO), false);
	data->xpm_tile = mlx_load_xpm42("textures/tile.xpm42");
	if (!data->xpm_tile)
		return (ft_putendl_fd("tile was not found", STDOUT_FILENO), false);
	data->xpm_wall = mlx_load_xpm42("textures/wall.xpm42");
	if (!data->xpm_wall)
		return (ft_putendl_fd("wall was not found", STDOUT_FILENO), false);
	data->xpm_pickup = mlx_load_xpm42("textures/pickup.xpm42");
	if (!data->xpm_pickup)
		return (ft_putendl_fd("pickup was not found", STDOUT_FILENO), false);
	data->bg = mlx_texture_to_image(data->mlx, &data->xpm_bg->texture);
	data->character = mlx_texture_area_to_image(data->mlx, \
											&data->xpm_char->texture, xy, wh2);
	data->tile = mlx_texture_to_image(data->mlx, &data->xpm_tile->texture);
	data->wall = mlx_texture_to_image(data->mlx, &data->xpm_wall->texture);
	data->pickup = mlx_texture_to_image(data->mlx, &data->xpm_pickup->texture);
	return (true);
}

static void	hooks(void	*imgdata)
{
	t_imgdata *const	imgdata2 = imgdata;

	if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(imgdata2->mlx);
	if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_S))
		imgdata2->character->instances[0].y += 32;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_W))
		imgdata2->character->instances[0].y -= 32;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_A))
		imgdata2->character->instances[0].x -= 32;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_D))
		imgdata2->character->instances[0].x += 32;
}

int32_t	graphics(char ***map, t_line *line)
{
	t_imgdata		imgdata;
	int32_t			colour;
	int32_t			i;

	i = 0;
	colour = 0;
	ft_bzero(&imgdata, sizeof(t_imgdata));
	imgdata.mlx = mlx_init(670, 190, "yoooo", true);
	if (!imgdata.mlx)
		return (0);
	if (!loading_images(&imgdata))
		return (0);
	images_to_window(&imgdata, *map, line);
	mlx_loop_hook(imgdata.mlx, &hooks, &imgdata);
	mlx_loop(imgdata.mlx);
	mlx_terminate(imgdata.mlx);
	return (0);
}
