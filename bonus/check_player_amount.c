/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_amount.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:42:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/17 03:54:06 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * Cannot have more than one starting location, as this code is not intended
 * to handle multiple players (...Yet?)
 */
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
