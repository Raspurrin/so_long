/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/27 22:17:33 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * Initialises random movements every SPEED amount of frames, 
 * so the random movements are repeated for that amount, otherwise the enemies
 * actually move like they are on speed. If ghosts go to the left or right, 
 * a new image will be used that matches the direction they are going.
 * A higher value of FATBOO will slow down the movement.
 */
static void	enemy_move(t_imgdata *data, t_enemy *enemy, size_t i, size_t j)
{
	if (data->count[FRAME] % SPEED == 0)
	{
		if (j == 0)
			enemy->move[j][i] = rand() % 4;
		else 
			enemy->move[j][i] = rand() % 2;
	}
	if (enemy->move[j][i] == 0 && enemy->x[0] - (BLOK / FATBOO) > 0 + BLOK)
	{
		if (j == 0)
			animate_ghosts(data, enemy->ghost, enemy, i, j);
		else
			enemy->pink_anim.dir = PINK_L;
		if (j == 0 || (j == 1 && (data->map[enemy->y[0] / BLOK + 1][enemy->x[0] / BLOK- 1] != '0')))
		(data->enemy_diff.lal[j])[i]->instances[0].x -= BLOK / FATBOO;
	}
	else if (enemy->move[j][i] == 1 && enemy->x[0] + (BLOK / FATBOO) \
											< data->width - (BLOK * 2))
	{
		if (j == 0)
			animate_ghosts(data, enemy->ghost_r, enemy, i, j);
		else
			enemy->pink_anim.dir = PINK;
		if (j == 0 || (j == 1 && (data->map[enemy->y[0] / BLOK + 1][enemy->x[0] / BLOK + 1] != '0')))
			(data->enemy_diff.lal[j])[i]->instances[0].x += (BLOK / FATBOO);
	}
	else if (enemy->move[j][i] == 2 && enemy->y[0] + (BLOK / FATBOO) \
									< data->height - (BLOK * 2))
		(data->enemy_diff.lal[j])[i]->instances[0].y += (BLOK / FATBOO);
	else if (enemy->move[j][i] == 3 && enemy->y[0] - (BLOK / FATBOO) > 0 + BLOK)
		(data->enemy_diff.lal[j])[i]->instances[0].y -= (BLOK / FATBOO);
}

/**
 * If the player is one block above an enemy and kill mode is on, 
 * then add the enemy to the exception array to be skipped over in the general 
 * enemy loop and move the image out of the range of the window view to the right
 * It also move the player up to create a bouncing effect
 */
static void	kill_enemy(t_imgdata *data, int32_t *player, \
								t_enemy *enemy, size_t i, size_t j)
{
	if (player[Y] == (enemy->y[1] - 1) && player[X] == enemy->x[1] && KILL == 1 \
		&& data->enemy.time_lock == false)
	{
		if (player[Y] - 1 > 1)
			data->img[CHAR]->instances[0].y -= BLOK;
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
void	check_damage(t_imgdata *data, int32_t *player, \
									t_enemy *enemy, size_t i, size_t j)
{
	enemy->x[1] = enemy->x[0] / BLOK;
	enemy->y[1] = enemy->y[0] / BLOK;
	kill_enemy(data, player, enemy, i, j);
	if ((player[X] == enemy->x[1] && player[Y] == enemy->y[1]) \
		&& data->enemy.time_lock == false && IMMORTAL == 0)
	{
		data->jump_lock = false;
		enemy->time = mlx_get_time();
		enemy->time_lock = true;
		data->count[LIFE]--;
	}
}

/**
 * If the player has been hit, it activates a time_lock
 * for a certain amount of time where a red filter image is put on the screen.
 * Which is the same amount of time the player is temporarily untouchable.
 */
void	red_filter(t_imgdata *data, t_enemy *enemy)
{
	enemy->current_time = mlx_get_time();
	if (enemy->time_lock == true && !data->img[RED])
		colour_screen(data, RED, 0xFF000033);
	else if (enemy->time_lock == true && data->img[RED])
		data->img[RED]->enabled = true;
	if (enemy->time_lock == true && \
	enemy->current_time >= (enemy->time + 1))
	{
		enemy->time_lock = false;
		if (data->img[RED])
			data->img[RED]->enabled = false;
	}
}

/**
 * Executing the death and enemy_move function for every ghost 
 * seperately every frame. Skipping the ghosts stored in the exception array
 * when they have been taken away from the afterlife.
 */
void	enemies(t_imgdata *data, t_enemy *enemy, \
								size_t x, size_t y)
{
	size_t	i;
	size_t	j;
	int32_t	player[XY];

	i = 0;
	j = 0;
	player[X] = x;
	player[Y] = y;
	red_filter(data, enemy);
	while (data->enemy_diff.lal[j])
	{
		enemy->x[0] = ((data->enemy_diff.lal[j])[i]->instances[0].x);
		enemy->y[0] = ((data->enemy_diff.lal[j])[i]->instances[0].y);
		if (enemy->excep[j][i] == false)
		{
			check_damage(data, player, enemy, i, j);
			enemy_move(data, enemy, i, j);
			enemy->x[0] = ((data->enemy_diff.lal[j])[i]->instances[0].x);
			enemy->y[0] = ((data->enemy_diff.lal[j])[i]->instances[0].y);
			if (j == 1)
				animate_pinks(data, enemy, i, enemy->x[0], enemy->y[0]);
		}
		if (i == (enemy->counts[j] - 1))
		{
			j++;
			i = 0;
		}
		else
			i++;
	}
}
