/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_instance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:26:45 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/22 21:24:38 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"

int32_t	find_c_instance(t_imgdata *data, size_t x_max, size_t y_max)
{
	size_t	x;
	size_t	y;
	int32_t	instance;

	x = 0;
	y = 0;
	instance = 0;
	while (y <= y_max)
	{
		while (x <= data->line.size)
		{
			if (data->map[y][x] == 'C' || data->map[y][x] == 'K')
				instance++;
			x++;
			if (y == y_max && x == x_max - 1)
				break ;
		}
		x = 0;
		y++;
	}
	return (instance);
}

void	check_player_amount(t_error *errors, t_imgdata *data)
{
	char	*foundchar;

	foundchar = ft_strchr(data->bigass, 'P');
	if (foundchar)
	{
		if (ft_strchr(foundchar + 1, 'P'))
			errors->morecharacters = true;
	}
}
