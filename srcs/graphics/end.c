/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:42:31 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/06 04:03:37 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Kills the child process with background music, deleting some images, 
 * closing the window and terminates the MLX instance. 
 * Put this in a seperate function, because it is also needed when 
 * just pressing ESCAPE instead of any key at the end of the game. 
 */
void	terminate(t_imgdata *data)
{
	mlx_delete_image(data->mlx, data->img[GREY]);
	mlx_delete_image(data->mlx, data->img[SCREEN]);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_2d(data->map);
	free(data->bigass);
	exit(1);
}

/**
 * Calling end with a keyhook, so I can wait for -any- key input
 * at the end of the game before terminating everything.
 */
void	end(mlx_key_data_t keydata, void *data)
{
	t_imgdata *const	data2 = data;

	if (mlx_is_key_down(data2->mlx, keydata.key))
		terminate(data);
}
