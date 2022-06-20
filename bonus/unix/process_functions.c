/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:43:56 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/20 16:25:25 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	kill_process(t_imgdata *data)
{
	kill(data->pid, SIGKILL);
}

void	gameloop_unix(t_imgdata *data)
{
	const char			*args[] = {AUDIO, "./audio/scape.wav", NULL};

	data->pid = fork();
	if (data->pid == 0)
	{
		execvp(args[0], (char **)args);
		exit(1);
	}
	else
	{
		if (!(mlx_loop_hook(data->mlx, &hook, data)))
			(error_close_window(data, "loop hook failed"));
		mlx_loop(data->mlx);
	}
}