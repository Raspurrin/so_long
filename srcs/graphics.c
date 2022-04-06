/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:27:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/06 23:29:15 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42.h"

void	hooks(void	*imgdata)
{
	t_imgdata	*imgdata2;

	imgdata2 = (t_imgdata *) imgdata;
	if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(imgdata2->mlx);
	if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_S))
		imgdata2->img->instances[0].y += 10;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_W))
		imgdata2->img->instances[0].y -= 10;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_A))
		imgdata2->img->instances[0].x -= 10;
	else if (mlx_is_key_down(imgdata2->mlx, MLX_KEY_D))
		imgdata2->img->instances[0].x += 10;
}

// void	*resizin(int32_t width, int32_t height, void *param)
// {
// 	if () // what do you use to detect someone trying to drag a window? o-o
// 		mlx_resize_image(imgdata2->img, width += 10, height);
// 	if ()
// 		mlx_resize_image(imgdata2->img, width -= 10, height);
// 	if ()
// 		mlx_resize_image(imgdata2->img, width, height += 10);
// 	if ()
// 		mlx_resize_image(imgdata2->img, width, height -= 10);
// }

int32_t	graphics(void)
{
	t_imgdata		imgdata;
	int32_t			x;
	int32_t			y;

	x = 0;
	y = 0;
	ft_bzero(&imgdata, sizeof(t_imgdata));
	imgdata.mlx = mlx_init(1600, 1000, "yoooo", true);
	if (!imgdata.mlx)
		return (0);
	imgdata.img = mlx_new_image(imgdata.mlx, 200, 200);
	mlx_image_to_window(imgdata.mlx, imgdata.img, 800, 500);
	while (y <= 200)
	{
		while (x <= 200)
			mlx_put_pixel(imgdata.img, x++, y, 0xFFFFFFFF);
		mlx_put_pixel(imgdata.img, x, y, 0xFFFFFFFF);
		x = 0;
		y++;
	}
	mlx_loop_hook(imgdata.mlx, &hooks, (void *)&imgdata);
	// mlx_resize_hook(imgdata.mlx, &resizin, (void *)&imgdata);
	mlx_loop(imgdata.mlx);
	mlx_terminate(imgdata.mlx);
	return (0);
}

// void	closin(void *mlx)
// {
// 	mlx_t	*mlx2;

// 	mlx2 = (mlx_t *)mlx;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// }

// mlx_key_hook(mlx, &hooks, (void *)&img);
// mlx_close_hook(imgdata->mlx, &closin, (void *)&imgdata->mlx);