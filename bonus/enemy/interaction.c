/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/30 20:42:16 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	enemy_move2(t_imgdata *data, t_enemy *enemy, size_t i, size_t j)
{
	if (enemy->move[j][i] == 1 && enemy->x[0] + (BLOK / FATBOO) \
											< data->width - (BLOK * 2))
	{
		if (j == 0)
			animate_ghosts(data, enemy->ghost_r, i, j);
		else
			enemy->pink_anim.dir = PINK_R;
		if (((data->map[enemy->y[0] / BLOK + 1][enemy->x[0] / BLOK + 1] != '0') \
														&& j == 1) || j == 0)
			(data->enemy_diff.lal[j])[i]->instances[0].x += (BLOK / FATBOO);
	}
	else if (enemy->move[j][i] == 2 && enemy->y[0] + (BLOK / FATBOO) \
									< data->height - (BLOK * 2))
		(data->enemy_diff.lal[j])[i]->instances[0].y += (BLOK / FATBOO);
	else if (enemy->move[j][i] == 3 && enemy->y[0] - (BLOK / FATBOO) > 0 + BLOK)
		(data->enemy_diff.lal[j])[i]->instances[0].y -= (BLOK / FATBOO);
}

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
			animate_ghosts(data, enemy->ghost, i, j);
		else
			enemy->pink_anim.dir = PINK_L;
		if (((data->map[enemy->y[0] / BLOK + 1][enemy->x[0] / BLOK - 1] != '0') \
														&& j == 1) || j == 0)
			(data->enemy_diff.lal[j])[i]->instances[0].x -= BLOK / FATBOO;
	}
	enemy_move2(data, enemy, i, j);
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

void	enemy_exec(t_imgdata *data, size_t i, size_t j, int32_t	*player)
{
	check_damage(data, player, i, j);
	enemy_move(data, &data->enemy, i, j);
	data->enemy.x[0] = ((data->enemy_diff.lal[j])[i]->instances[0].x);
	data->enemy.y[0] = ((data->enemy_diff.lal[j])[i]->instances[0].y);
	if (j == 1)
		animate_pinks(data, i, data->enemy.x[0], data->enemy.y[0]);
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
			enemy_exec(data, i, j, player);
		if (i == (enemy->counts[j] - 1))
		{
			j++;
			i = 0;
		}
		else
			i++;
	}
}
