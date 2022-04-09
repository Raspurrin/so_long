/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/10 01:25:16 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42.h"

void	images_to_window(t_imgdata *data, char **map, \
						t_line *line, size_t blocksize)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	printf("linecount: %zd\n", line->count);
	printf("linesize: %zd\n", line->size);
	// line = NULL;
	// printf("yo:%s %s %s %s\n", map[x], map[1], map[2], map[3]);
	// mlx_image_to_window(data->mlx, data->wall, x * 32, y * 32);
	// mlx_image_to_window(data->mlx, data->wall, 32, 32);
	mlx_image_to_window(data->mlx, data->bg, 0, 0);
	while (map[y])
	{
		// printf("y: %zd", y);
		while (map[y][x])
		{
			printf("linecount: %zu y: %zu linesize %zu x: %zu \n", line->count, y, line->size, x);
			if (map[y][x] == '1')
			{
				if (x == 0 || y == 0 || y == 5 || x == 20)
				{
					printf("inside if - y: %zu x: %zu\n", y, x);
					int a = mlx_image_to_window(data->mlx, data->wall, x * blocksize, y * blocksize);
					mlx_set_instance_depth(&data->wall->instances[a], 20);
				}
				else
				{
					mlx_image_to_window(data->mlx, data->tile, x * blocksize, y * blocksize);
					// mlx_set_instance_depth(&data->tile->instances[b], 9001);

				}
			}
			// else 
			// 	mlx_image_to_window(data->mlx, data->pickup, x * 32, y * 32);
			if (map[y][x] == 'C')
				mlx_image_to_window(data->mlx, data->pickup, x * blocksize, y * blocksize);
			if (map[y][x] == 'E')
				mlx_image_to_window(data->mlx, data->pickup, x * blocksize, y * blocksize);
			if (map[y][x] == 'P')
				mlx_image_to_window(data->mlx, data->character, x * blocksize, y * blocksize);
			x++;
		}
		x = 0;
		y++;
	}
}
	// for testing replace this with above code: 

	// line = NULL;
	// map = NULL;
	// mlx_image_to_window(data->mlx, data->bg, 0, 0);
	// mlx_image_to_window(data->mlx, data->slime, 20, 20);
	// mlx_image_to_window(data->mlx, data->tile, 300, 100);
	// mlx_image_to_window(data->mlx, data->wall, 200, 100);
	// mlx_image_to_window(data->mlx, data->pickup, 100, 100);
	// mlx_image_to_window(data->mlx, data->character, 20, 20);

