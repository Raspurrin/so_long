/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:42:31 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/31 03:21:18 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * Kills the child process with background music, deleting some images, 
 * closing the window and terminates the MLX instance. 
 * Put this in a seperate function, because it is also needed when 
 * just pressing ESCAPE instead of any key at the end of the game. 
 */
void	terminate(t_imgdata *data)
{
	kill(data->pid, SIGKILL);
	exit(0);
	mlx_delete_image(data->mlx, data->img[GREY]);
	mlx_delete_image(data->mlx, data->img[SCREEN]);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free(data->map);
	free(data->bigass);
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

/**
 * Puts a different message on the screen depending if you died 
 * or won the game with different offsets.  
 */
void	end_message(t_imgdata *data)
{
	if (data->count[LIFE] <= 0)
		display_message(data, true, 3.5, 3);
	else
		display_message(data, false, 3, 3);
	mlx_key_hook(data->mlx, &end, data);
}
