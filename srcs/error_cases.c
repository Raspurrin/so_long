/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:09:44 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/22 21:33:12 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	error_output(t_error *errors, t_line *line)
{
	if (errors->cpe == true || errors->different_input == true \
		|| errors->file_name == true || errors->rectangular == true \
		|| errors->walls == true || errors->morecharacters == true \
		|| errors->enemyoverflow == true || line->count == 0)
	{
		errors->error = true;
		ft_putendl_fd("Error", STDOUT_FILENO);
	}
	if (errors->cpe == true)
		ft_putendl_fd("Does not contain at least 1 collectible, \
map exit and starting position", STDOUT_FILENO);
	if (errors->different_input == true)
		ft_putendl_fd("Contains input other than 01CEP", STDOUT_FILENO);
	if (errors->rectangular == true)
		ft_putendl_fd("Map is not rectangular", STDOUT_FILENO);
	if (errors->walls == true)
		ft_putendl_fd("Map is not surrounded by walls", STDOUT_FILENO);
	if (errors->morecharacters == true)
		ft_putendl_fd("Map contains too many characters", STDOUT_FILENO);
	if (errors->enemyoverflow == true)
		ft_putendl_fd("Enemy request too large", STDOUT_FILENO);
	return ;
}
