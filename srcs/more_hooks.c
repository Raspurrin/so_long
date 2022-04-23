/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:46:08 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/22 21:47:40 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	enemy_move2(t_imgdata *data, size_t *i, size_t *x, size_t *y)
{
	if (data->move[*i] == 0 \
							&& data->map[*y + 1][*x] != '1')
				data->img[GHOST]->instances[*i].y += BLOK / 20;
	else if (data->move[*i] == 1 \
							&& data->map[*y - 1][*x] != '1' && y - 1 != 0)
		data->img[GHOST]->instances[*i].y -= BLOK / 20;
	else if (data->move[*i] == 2 \
							&& data->map[*y][*x - 1] != '1')
		data->img[GHOST]->instances[*i].x -= BLOK / 20;
	else if (data->move[*i] == 3 \
							&& data->map[*y][*x + 1] != '1')
		data->img[GHOST]->instances[*i].x += BLOK / 20;
}

void	enemy_move(void	*data)
{
	t_imgdata *const	data2 = data;
	size_t				i;
	size_t				x;
	size_t				y;

	i = 0;
	while (i < ENEMYCOUNT)
	{
		x = (data2->img[GHOST]->instances[i].x / BLOK);
		y = (data2->img[GHOST]->instances[i].y / BLOK);
		if (data2->counter % 18 == 0)
			data2->move[i] = rand() % 4;
		enemy_move2(data2, &i, &x, &y);
		i++;
	}
	data2->counter++;
}
