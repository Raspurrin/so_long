/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 23:11:37 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/17 05:22:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * Changes the index of the ghost into an x and y position
 * and puts that established position in the compare array for future comparisons
 * @param data 
 * @param compare an array containing all established ghost starting positions
 * @param index the index of the ghost pos in a big ass string containing the map
 * @param i keeps count of the ghosts
 */
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

/**
 * @brief Get a random number within possible locations. Itterate through them
 * as long as it's not an empty tile and then verify if the spawn location
 * has not already been taken yet.
 * @param data->bigass contains the map in one big ass string. 
 */
void	get_ghost_spawn(t_imgdata *data, t_line *line)
{
	size_t	i;
	size_t	j;
	size_t	index;
	size_t	*compare;

	i = 0;
	compare = calloc(GHOSTCOUNT, sizeof(size_t));
	while (i < GHOSTCOUNT)
	{
		index = (rand() % ((line->size + 1) * (line->count - 1)) \
													+ line->size + 1);
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
