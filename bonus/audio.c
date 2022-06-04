/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:34:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/04 22:35:52 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	kurwa_audio(char *args[])
{
	int32_t		status;
	int32_t		pid;

	pid = fork();
	if (pid == 0)
	{
		execvp(args[0], (char **)args);
		waitpid(pid, &status, 0);
		kill(pid, SIGKILL);
	}
}