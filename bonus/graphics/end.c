/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:42:31 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/04 02:42:26 by mialbert         ###   ########.fr       */
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
	mlx_delete_image(data->mlx, data->img[GREY]);
	mlx_delete_image(data->mlx, data->img[SCREEN]);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_2d(data->map);
	free(data->bigass);
	exit(0);
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
	const char	*victory_audio[] = {"/usr/bin/afplay", "--volume", \
	"1", "./audio/victory.wav", NULL};
	const char	*gameover_audio[] = {"/usr/bin/afplay", "--volume", \
	"1", "./audio/jump.wav", NULL};

	if (!data->img[SCREEN])
	{
		colour_screen(data, GREY, 0x303388);
		if (data->count[LIFE] <= 0)
		{
			display_message(data, true, 3.5, 3);
			kurwa_audio((char **)gameover_audio);
		}
		else
		{
			display_message(data, false, 3, 3);
			kurwa_audio((char **)victory_audio);
		}
	}
	if (data->count[ENDFRAME] >= 20)
		mlx_key_hook(data->mlx, &end, data);
	data->count[ENDFRAME]++;
}
