/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/09 22:06:45 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42.h"

static void	loading_images(t_imgdata *data)
{
	uint32_t		xy[] = {50, 50};
	uint32_t		wh2[] = {50, 30};

	data->xpm_bg = mlx_load_xpm42("textures/merged.xpm42");
	data->xpm_char = mlx_load_xpm42("textures/main.xpm42");
	// data->xpm_slime = mlx_load_xpm42("textures/slimes_frames_all.xpm42");
	data->xpm_tile = mlx_load_xpm42("textures/tile.xpm42");
	data->xpm_wall = mlx_load_xpm42("textures/wall.xpm42");
	data->xpm_pickup = mlx_load_xpm42("textures/pickup.xpm42");
	data->bg = mlx_texture_to_image(data->mlx, &data->xpm_bg->texture);
	// data->slime = mlx_texture_area_to_image(data->mlx, \
	// 										&data->xpm_slime->texture, xy, wh2);
	data->character = mlx_texture_area_to_image(data->mlx, \
											&data->xpm_char->texture, xy, wh2);
	data->tile = mlx_texture_to_image(data->mlx, &data->xpm_tile->texture);
	data->wall = mlx_texture_to_image(data->mlx, &data->xpm_wall->texture);
	data->pickup = mlx_texture_to_image(data->mlx, &data->xpm_pickup->texture);
}

static void	hooks(void	*imgdata)
{
	t_imgdata *const	imgdata2 = imgdata;
	// uint8_t				*startingpoint;

	// startingpoint = imgdata2->character->pixels;
	//uint8_t	test = ((uint8_t)(mlx_get_time() % 4 * 10));
	// printf("%d", mlx_get_time() % 4 * 10);
	// if ((imgdata2->character->pixels - imgdata2->startingpoint) >= 60)
	// 	imgdata2->character->pixels = imgdata2->startingpoint;
	// imgdata2->character->pixels += ((uint8_t)(mlx_get_time() % 4 * 20));
	// imgdata2->character->pixels += 40;

	if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(imgdata2->mlx);
	if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_S))
		imgdata2->character->instances[0].y += 10;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_W))
		imgdata2->character->pixels += 40;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_A))
		imgdata2->character->instances[0].x -= 10;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_D))
		imgdata2->character->instances[0].x += 10;
}

int32_t	graphics(char ***map, t_line *line) // get these params
{
	t_imgdata		imgdata;
	int32_t			colour;
	int32_t			i;

	i = 0;
	colour = 0;
	printf("linecount in graphics: %zd\n", line->count);
	// printf("%s", *map[1]);
	ft_bzero(&imgdata, sizeof(t_imgdata));
	imgdata.mlx = mlx_init(670, 190, "yoooo", true);
	// imgdata.mlx = mlx_init(line->size * 32, line->count * 32, "yoooo", true);
	if (!imgdata.mlx)
		return (0);
	loading_images(&imgdata);
	images_to_window(&imgdata, *map, line);
	// imgdata.startingpoint = imgdata.character->pixels;
	mlx_loop_hook(imgdata.mlx, &hooks, &imgdata);
	mlx_loop(imgdata.mlx);
	mlx_terminate(imgdata.mlx);
	return (0);
}
	// while (i < 4)
	// {
	// 	imgdata.character[i++] = mlx_texture_area_to_image(imgdata.mlx, &imgdata.xpm_char->texture, xy, wh);
	// 	xy[0] += 50;
	// }

	// ft_memset(imgdata.img2, 1, sizeof(imgdata.img2));
	// while (y <= 200)
	// {
	// 	while (x <= 200)
	// 		mlx_put_pixel(imgdata.img, x++, y, colour++);
	// 	mlx_put_pixel(imgdata.img, x, y, colour++);
	// 	x = 0;
	// 	y++;
	// }