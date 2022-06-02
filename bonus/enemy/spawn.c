/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 23:11:37 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/02 05:31:57 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * @brief Get a random number within possible locations. Itterate through them
 * as long as it's not an empty tile and then verify if the spawn location
 * has not already been taken yet.
 * 	if (enemy->ghost_spawn[j]) index = 0; is for the case that it won't reach
 * the end of the comparison string because the index is found in there.
 * @param data->bigass contains the map in one big ass string. 
 */
void	get_ghost_spawn(t_imgdata *data, t_enemy *enemy, t_line *line)
{
	ssize_t	i;
	size_t	j;
	ssize_t	index;

	i = 0;
	ft_memset(enemy->ghost_spawn, -1, sizeof(enemy->ghost_spawn));
	while (i < GHOSTCOUNT)
	{
		index = (rand() % ((line->size + 1) * (line->count - 1)) \
													+ line->size + 1);
		j = 0;
		while ((data->bigass[index] != '0' && data->bigass[index]))
		{
			index++;
			if (!(data->bigass[index]))
				index = -1;
		}
		while (index != -1 && enemy->ghost_spawn[j] \
					&& enemy->ghost_spawn[j] != index)
			j++;
		if (enemy->ghost_spawn[j])
			index = -1;
		if (index != -1)
			enemy->ghost_spawn[i++] = index;
	}
}

static ssize_t	*calloc_avail(t_imgdata *data, t_line *line)
{
	ssize_t	*avail;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	while (data->bigass[i++])
	{
		if (data->bigass[i] == '1' && i - (line->size + 1) > 0)
		{
			if (data->bigass[i - (line->size + 1)] == '0')
				j++;
		}
	}
	if (j < PINKCOUNT)
		return (ft_putendl_fd("Error\nNot enough spawn locations for pink", \
						STDOUT_FILENO), NULL);
	avail = calloc(j + 1, sizeof(ssize_t));
	return (avail);
}

static ssize_t	*avail_ground_spawn(t_imgdata *data, t_line *line, \
												size_t *spawn_count)
{
	ssize_t	*avail;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	avail = calloc_avail(data, &data->line);
	if (!avail)
		return (0);
	while (data->bigass[i++])
	{
		if (data->bigass[i] == '1' && i - (line->size + 1) > 0)
		{
			if (data->bigass[i - (line->size + 1)] == '0')
				avail[j++] = i - (line->size + 1);
		}
	}
	*spawn_count = j;
	return (avail);
}

bool	get_pink_spawn(t_imgdata *data, t_line *line, t_enemy *enemy)
{
	size_t	i;
	size_t	j;
	size_t	spawn_count;
	ssize_t	*avail;
	ssize_t	index;

	i = 0;
	ft_memset(enemy->pink_spawn, -1, sizeof(enemy->pink_spawn));
	avail = avail_ground_spawn(data, line, &spawn_count);
	if (!avail)
		return (false);
	while (i < PINKCOUNT)
	{
		j = 0;
		index = rand() % spawn_count;
		while (enemy->pink_spawn[j] && enemy->pink_spawn[j] != avail[index])
			j++;
		if (enemy->pink_spawn[j])
			index = -1;
		if (index != -1)
			enemy->pink_spawn[i++] = avail[index];
	}
	free(avail);
	return (true);
}
