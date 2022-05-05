/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/04 15:10:08 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	enemy_move(t_imgdata *data, t_enemy *enemy, size_t i)
{
	const int32_t	x = enemy->img[i]->instances[0].x;
	const int32_t	y = enemy->img[i]->instances[0].y;

	if (data->count[FRAME] % SPEED == 0)
		enemy->move[i] = rand() % 4;
	if (enemy->move[i] == 0 && y + (BLOK / FATBOO) < data->height - (BLOK * 2))
		enemy->img[i]->instances[0].y += (BLOK / FATBOO);
	else if (enemy->move[i] == 1 && y - (BLOK / FATBOO) > 0 + BLOK)
		enemy->img[i]->instances[0].y -= (BLOK / FATBOO);
	else if (enemy->move[i] == 2 && x - (BLOK / FATBOO) > 0 + BLOK)
	{
		animate_ghosts(data, data->ghost, x, y, i);
		enemy->img[i]->instances[0].x -= BLOK / FATBOO;
	}
	else if (enemy->move[i] == 3 && x + (BLOK / FATBOO) < data->width \
														- (BLOK * 2))
	{
		animate_ghosts(data, data->ghost_r, x, y, i);
		enemy->img[i]->instances[0].x += (BLOK / FATBOO);
	}
}

static void	death(t_imgdata *data, size_t *player, t_enemy *enemy, size_t i)
{
	const size_t	ghost_x = (enemy->img[i]->instances[0].x / BLOK);
	const size_t	ghost_y = (enemy->img[i]->instances[0].y / BLOK);

	if (player[Y] == (ghost_y - 1) && player[X] == ghost_x && KILL == 1)
	{
		if (player[Y] - 1 > 1)
			data->img[CHAR]->instances[0].y -= BLOK;
		enemy->img[i]->instances[0].x += data->width;
		data->enemy.excep[i] = 1;
	}
	else if ((player[X] == ghost_x && player[Y] == ghost_y) && data->enemy.time_lock == false \
														&& IMMORTAL == 0)
	{
		data->enemy.enemy_time = mlx_get_time();
		data->enemy.time_lock = true;
		data->count[LIFE]--;
		if (player[X] - 1 > 1)
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
	size_t	player[XY];

	i = 0;
	player[X] = x;
	player[Y] = y;
	enemy->current_time = mlx_get_time();
	if (enemy->time_lock == true && \
	enemy->current_time == (enemy->enemy_time + 2))
	enemy->time_lock = false;
	while (i < ENEMYCOUNT)
	{
		if (enemy->excep[i] == 0)
			death(data, player, enemy, i);
		if (enemy->excep[i] == 0)
			enemy_move(data, enemy, i);
		i++;
	}
	data->count[FRAME]++;
}

void	get_enemy_spawn(t_imgdata *data, t_enemy *enemy)
{
	size_t	i;
	size_t	j;
	size_t	index;
	size_t	*compare;

	i = 0;
	compare = malloc(ENEMYCOUNT * sizeof(size_t));
	while (i < ENEMYCOUNT)
	{
		index = (rand() % ((data->line.size + 1) * (data->line.count - 1))) \
													+ data->line.size + 1;
		j = 0;
		while ((data->bigass[index] != '0' && data->bigass[index]))
		{
			index++;
			if (!(data->bigass[index]))
				index = 0;
		}
		while (index != 0 && compare[j] && compare[j] != index)
			j++;
		if (compare[j])
			index = 0;
		if (index != 0)
		{
			compare[i] = index;
			enemy->x[i] = index % (data->line.size + 1);
			enemy->y[i] = index / (data->line.size + 1);
			i++;
		}
	}
}

bool	enemy_to_window(t_imgdata *data, t_enemy *enemy)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		x = enemy->x[i];
		y = enemy->y[i];
		if (x > 29 || y > 13)
			printf("heyhey");
		mlx_image_to_window(data->mlx, enemy->img[i], \
												x * BLOK, y * BLOK);
		i++;
		// return (free_array(data->img, "image_to_window failed"), false);
	}
	return (true);
}
