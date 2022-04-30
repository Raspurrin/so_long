/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/30 19:01:41 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	enemy_move(t_imgdata *data, t_enemy *enemy, size_t i)
{
	const size_t	x = (data->img[GHOST]->instances[i].x / BLOK);
	const size_t	y = (data->img[GHOST]->instances[i].y / BLOK);

	if (data->counter % SPEED == 0)
		enemy->move[i] = rand() % 4;
	if (enemy->move[i] == 0 && data->map[y + 1][x] != '1')
		data->img[GHOST]->instances[i].y += BLOK / FATBOO;
	else if (enemy->move[i] == 1 && data->map[y][x] != '1')
		data->img[GHOST]->instances[i].y -= BLOK / FATBOO;
	else if (enemy->move[i] == 2 && data->map[y][x] != '1')
		data->img[GHOST]->instances[i].x -= BLOK / FATBOO;
	else if (enemy->move[i] == 3 && data->map[y][x + 1] != '1')
		data->img[GHOST]->instances[i].x += BLOK / FATBOO;
}

static void	death(t_imgdata *data, size_t x, size_t y, size_t i)
{
	const size_t	ghost_x = (data->img[GHOST]->instances[i].x / BLOK);
	const size_t	ghost_y = (data->img[GHOST]->instances[i].y / BLOK);

	if (y == (ghost_y - 1) && x == ghost_x && KILL == 1)
	{
		if (data->map[y - 1][x] != '1' && y - 1 > 1)
			data->img[CHAR]->instances[0].y -= BLOK;
		data->img[GHOST]->instances[i].x += data->width;
		data->enemy.excep[data->enemy.excep_count++] = i;
	}
	else if ((x == ghost_x && y == ghost_y) && data->enemy.time_lock == false \
														&& IMMORTAL == 0)
	{
		data->enemy.enemy_time = mlx_get_time();
		data->enemy.time_lock = true;
		data->count[LIFE]--;
		if (data->map[y][x - 2] != '1')
			data->img[CHAR]->instances[0].x -= (BLOK * 2);
		else
			data->img[CHAR]->instances[0].x += (BLOK * 2);
	}
	if (data->count[LIFE] == 0)
	{
		display_message(data, true, 3.5, 3);
		mlx_key_hook(data->mlx, &end, data);
	}
}

void	enemies(t_imgdata *data, t_enemy *enemy, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	enemy->current_time = mlx_get_time();
	if (enemy->time_lock == true && \
	enemy->current_time == (enemy->enemy_time + 2))
	enemy->time_lock = false;
	while (i < ENEMYCOUNT)
	{
		if (i != enemy->excep[i])
		{
			death(data, x, y, i);
			enemy_move(data, enemy, i);
		}
		i++;
	}
	data->counter++;
}

void	get_enemy_spawn(t_imgdata *data)
{
	size_t	i;
	size_t	index;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		index = (rand() % ((data->line.size + 1) * (data->line.count - 1))) \
													+ data->line.size + 1;
		while (data->bigass[index] != '0' && data->bigass[index])
		{
			index++;
			if (!(data->bigass[index]))
				index = 0;
		}
		if (index != 0)
		{
			data->enemy.enemy_x[i] = index % (data->line.size + 1);
			data->enemy.enemy_y[i] = index / (data->line.size + 1);
			i++;
		}
	}
}

bool	enemy_to_window(t_imgdata *data, \
						size_t *x, size_t *y)
{
	size_t	i;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		if (*y == data->enemy.enemy_y[i] && *x == data->enemy.enemy_x[i] \
			&& i < ENEMYCOUNT)
		{
			mlx_image_to_window(data->mlx, data->img[GHOST], \
												*x * BLOK, *y * BLOK);
				// return (free_array(data->img, "image_to_window failed"), false);
		}
		i++;
	}
	return (true);
}
