/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 02:23:46 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/18 02:15:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * If the player is one block above an enemy and kill mode is on, 
 * then add the enemy to the exception array to be skipped over in the general 
 * enemy loop and move the image out of the range of the window view to the right
 * It also move the player up to create a bouncing effect
 */
void	kill_enemy(t_imgdata *data, int32_t *player, size_t i, size_t j)
{
	const char	*bump_audio[] = {AUDIO, "./audio/bump.wav", NULL};

	if (player[Y] == (data->enemy.y[1] - 1) && player[X] == data->enemy.x[1] \
								&& KILL == 1 && data->enemy.time_lock == false)
	{
		kurwa_audio((char **)bump_audio);
		if (player[Y] - 1 > 1)
			data->img[CHAR_R]->instances[0].y -= BLOK;
		(data->enemy_diff.lal[j])[i]->instances[0].x += data->width;
		data->enemy.excep[j][i] = true;
	}
}

/**
 * Tracks if the position of an enemy overlaps with the player position if the 
 * time lock is off and there is no immortality. 
 * If it does, decreases the life counter and activates the time_lock for 
 * temporary player invulnerability. 
 */
void	check_damage(t_imgdata *data, int32_t *player, size_t i, size_t j)
{
	const char	*hurt_audio[] = {AUDIO, "./audio/hurt.wav", NULL};
	const char	*hurt2_audio[] = {AUDIO, "./audio/hurt2.wav", NULL};

	data->enemy.x[1] = data->enemy.x[0] / BLOK;
	data->enemy.y[1] = data->enemy.y[0] / BLOK;
	kill_enemy(data, player, i, j);
	if ((player[X] == data->enemy.x[1] && player[Y] == data->enemy.y[1]) \
		&& data->enemy.time_lock == false && IMMORTAL == 0)
	{
		if (j == 0)
			kurwa_audio((char **)hurt2_audio);
		else
			kurwa_audio((char **)hurt_audio);
		data->jump_lock = false;
		data->enemy.time = mlx_get_time();
		data->enemy.time_lock = true;
		data->count[LIFE]--;
	}
}
