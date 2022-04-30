/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_amount.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:42:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/29 03:21:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
