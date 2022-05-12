/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 23:11:37 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/12 03:18:19 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

size_t	index_to_xy(t_imgdata *data, size_t *compare, size_t index, size_t i)
{
	if (index != 0)
	{
		compare[i] = index;
		data->enemy.x[i] = index % (data->line.size + 1);
		data->enemy.y[i] = index / (data->line.size + 1);
		i++;
	}
	return (i);
}

void	get_ghost_spawn(t_imgdata *data)
{
	size_t	i;
	size_t	j;
	size_t	index;
	size_t	*compare;

	i = 0;
	compare = calloc(GHOSTCOUNT, sizeof(size_t));
	while (i < GHOSTCOUNT)
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
		i = index_to_xy(data, compare, index, i);
	}
	free(compare);
}
