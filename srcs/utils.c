/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:46:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/22 21:25:56 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_2d(char **map)
{
	int32_t	i;

	i = 0;
	while (*map)
	{
		free(*map);
		map++;
	}
	return ;
}

size_t	getncount(char *str, uint8_t chr)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == chr)
			count++;
		str++;
	}
	return (count);
}
