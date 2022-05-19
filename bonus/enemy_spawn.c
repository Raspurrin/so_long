/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 23:11:37 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/19 20:17:28 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * @brief Get a random number within possible locations. Itterate through them
 * as long as it's not an empty tile and then verify if the spawn location
 * has not already been taken yet.
 * @param data->bigass contains the map in one big ass string. 
 */
void	get_ghost_spawn(t_imgdata *data, t_enemy *enemy, t_line *line)
{
	size_t	i;
	size_t	j;
	ssize_t	index;

	i = 0;
	enemy->ghost_spawn = calloc(GHOSTCOUNT, sizeof(ssize_t));
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
		while (index != 0 && enemy->ghost_spawn[j] && enemy->ghost_spawn[j] != index)
			j++;
		if (enemy->ghost_spawn[j])
			index = 0;
		if (index != 0)
			enemy->ghost_spawn[i++] = index;
	}
}

static ssize_t	*avail_ground_spawn(t_imgdata *data, t_line *line, \
												ssize_t *spawn_count)
{
	ssize_t	*compare;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	while (data->bigass[i++])
	{
		if (data->bigass[i] == '1' && i - line->count > 0)
		{
			if (data->bigass[i - line->count] == '0')
				j++;
		}
	}
	compare = calloc(j + 1, sizeof(ssize_t));
	i = 0;
	j = 0;
	while (data->bigass[i++])
	{
		if (data->bigass[i] == '1' && i - line->count > 0)
		{
			if (data->bigass[i - line->count] == '0')
				compare[j++] = i;
		}
	}
	*spawn_count = j;
	return (compare);
}

void	get_pink_spawn(t_imgdata *data, t_line *line, t_enemy *enemy)
{
	size_t	i;
	ssize_t	j;
	ssize_t	spawn_count;
	ssize_t	index;

	i = 0;
	enemy->pink_spawn = avail_ground_spawn(data, line, &spawn_count);
	while (i < PINKCOUNT)
	{
		j = 0;
		index = rand() % spawn_count;
		while (j < (spawn_count) && enemy->pink_spawn[j] != index)
			j++;
		if (enemy->pink_spawn[j])
			index = 0;
		if (index != 0)
		enemy->pink_spawn[i++] = index;
	}
}
