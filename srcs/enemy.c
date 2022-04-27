/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/28 00:32:36 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	enemy_move(t_imgdata *data, size_t i)
{
	const size_t	x = (data->img[GHOST]->instances[i].x / BLOK);
	const size_t	y = (data->img[GHOST]->instances[i].y / BLOK);

	if (data->counter % SPEED == 0)
		data->move[i] = rand() % 4;
	if (data->move[i] == 0 && data->map[y + 1][x] != '1')
		data->img[GHOST]->instances[i].y += BLOK / FATBOO;
	else if (data->move[i] == 1 && data->map[y - 1][x] != '1' \
												&& y - 1 != 0)
		data->img[GHOST]->instances[i].y -= BLOK / FATBOO;
	else if (data->move[i] == 2 && data->map[y][x - 1] != '1')
		data->img[GHOST]->instances[i].x -= BLOK / FATBOO;
	else if (data->move[i] == 3 && data->map[y][x + 1] != '1')
		data->img[GHOST]->instances[i].x += BLOK / FATBOO;
}

static void	death(t_imgdata *data, size_t x, size_t y, size_t i)
{
	const size_t	ghost_x = (data->img[GHOST]->instances[i].x / BLOK);
	const size_t	ghost_y = (data->img[GHOST]->instances[i].y / BLOK);

	if (y == (ghost_y - 1) && x == ghost_x)
	{
		data->img[CHAR]->instances[0].y -= BLOK;
		mlx_set_instance_depth(&data->img[GHOST]->instances[i], -999);
		data->excep[data->excep_count++] = i;
	}
	else if ((x == ghost_x && y == ghost_y) && data->time_lock == false)
	{
		data->enemy_time = mlx_get_time();
		data->time_lock = true;
		data->count[LIFE]--;
		if ((x - 2) != '1')
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

void	enemies(t_imgdata *data, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		if (i != data->excep[i])
		{
			death(data, x, y, i);
			enemy_move(data, i);
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
	while (i < ENEMYCOUNT && i < data->enemy_max)
	{
		index = rand() % ((data->line.size + 2) * (data->line.count - 1));
		while (data->bigass[index] != '0' && data->bigass[index])
		{
			index++;
			if (!(data->bigass[index]))
				index = 0;
		}
		if (index != 0)
		{
			data->enemy_x[i] = index % data->line.size;
			data->enemy_y[i] = index / data->line.size;
			i++;
		}
	}
}

void	enemy_to_window(t_imgdata *data, \
						size_t *x, size_t *y)
{
	size_t	i;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		if (*y == data->enemy_y[i] && *x == data->enemy_x[i] \
			&& i < ENEMYCOUNT && i < data->enemy_max)
		{
			mlx_image_to_window(data->mlx, data->img[GHOST], \
								*x * BLOK, *y * BLOK);
		}
		i++;
	}
	return ;
}
