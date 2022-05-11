/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/11 19:55:46 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	enemy_move(t_imgdata *data, t_enemy *enemy, size_t i)
{
	if (data->count[FRAME] % SPEED == 0)
		enemy->move[i] = rand() % 4;
	if (enemy->move[i] == 0 && enemy->y[0] + (BLOK / FATBOO) \
									< data->height - (BLOK * 2))
		enemy->img[i]->instances[0].y += (BLOK / FATBOO);
	else if (enemy->move[i] == 1 && enemy->y[0] - (BLOK / FATBOO) > 0 + BLOK)
		enemy->img[i]->instances[0].y -= (BLOK / FATBOO);
	else if (enemy->move[i] == 2 && enemy->x[0] - (BLOK / FATBOO) > 0 + BLOK)
	{
		animate_ghosts(data, data->ghost, enemy->x[0], enemy->y[0], i);
		enemy->img[i]->instances[0].x -= BLOK / FATBOO;
	}
	else if (enemy->move[i] == 3 && enemy->x[0] + (BLOK / FATBOO) < data->width \
														- (BLOK * 2))
	{
		animate_ghosts(data, data->ghost_r, enemy->x[0], enemy->y[0], i);
		enemy->img[i]->instances[0].x += (BLOK / FATBOO);
	}
}

static void	kill_enemy(t_imgdata *data, int32_t *player, \
								t_enemy *enemy, size_t i)
{
	if (player[Y] == (enemy->y[1] - 1) && player[X] == enemy->x[1] && KILL == 1 \
		&& data->enemy.time_lock == false)
	{
		if (player[Y] - 1 > 1)
			data->img[CHAR]->instances[0].y -= BLOK;
		enemy->img[i]->instances[0].x += data->width;
		data->enemy.excep[i] = 1;
	}
}

// ((player[X] == (enemy->x[1] + 1) || player[X] == (enemy->x[1] - 1)) \
// 		&& player[Y] == enemy->y[1]) ||

static void	death(t_imgdata *data, int32_t *player, t_enemy *enemy, size_t i)
{
	enemy->x[1] = enemy->x[0] / BLOK;
	enemy->y[1] = enemy->y[0] / BLOK;
	printf("player[X]: %d, player[Y]: %d\nx: %d, y: %d\n", player[X], player[Y], enemy->x[1], enemy->y[1]);
	kill_enemy(data, player, enemy, i);
	if ((player[X] == enemy->x[1] && player[Y] == enemy->y[1]) \
		&& data->enemy.time_lock == false && IMMORTAL == 0)
	{
		data->jump_lock = false;
		printf("yo time_lock == %d\n", data->enemy.time_lock);
		enemy->time = mlx_get_time();
		enemy->time_lock = true;
		data->count[LIFE]--;
		// if (player[X] - 1 > 1)
		// 	data->img[CHAR]->instances[0].x -= (BLOK * 2);
		// else
		// 	data->img[CHAR]->instances[0].x += (BLOK * 2);
	}
}

void	enemies(t_imgdata *data, t_enemy *enemy, size_t x, size_t y)
{
	size_t	i;
	int32_t	player[XY];

	i = 0;
	player[X] = x;
	player[Y] = y;
	enemy->current_time = mlx_get_time();
	if (data->enemy.time_lock == true && !data->img[RED])
		colour_screen(data, RED, 0xFF000033);
	else if (data->enemy.time_lock == true && data->img[RED])
		data->img[RED]->enabled = true;
	if (enemy->time_lock == true && \
	enemy->current_time >= (enemy->time + 1))
	{
		enemy->time_lock = false;
		if (data->img[RED])
			data->img[RED]->enabled = false;
	}
	while (i < GHOSTCOUNT)
	{
		enemy->x[0] = (enemy->img[i]->instances[0].x);
		enemy->y[0] = (enemy->img[i]->instances[0].y);
		if (enemy->excep[i] == 0)
			death(data, player, enemy, i);
		if (enemy->excep[i] == 0)
			enemy_move(data, enemy, i);
		i++;
	}
	data->count[FRAME]++;
}
