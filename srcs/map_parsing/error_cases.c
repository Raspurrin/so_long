/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:09:44 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/05 23:45:30 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * I made this to be able to output multiple error messages for the map
 * if multiple errors are true at the same time. And to not have 
 * error messages all over my input_handler functions
 */
void	error_output(t_error *errors, t_line *line)
{
	if (errors->no_cpe == true || errors->different_input == true \
		|| errors->file_name == true || errors->not_rectangular == true \
		|| errors->walls == true || errors->morecharacters == true \
		|| line->count == 0)
	{
		errors->error = true;
		ft_putendl_fd("Error", STDOUT_FILENO);
	}
	if (errors->no_cpe == true)
		ft_putendl_fd("Does not contain at least 1 collectible, \
		map exit and starting position", STDOUT_FILENO);
	if (errors->different_input == true)
		ft_putendl_fd("Contains input other than 01CEP", STDOUT_FILENO);
	if (errors->not_rectangular == true)
		ft_putendl_fd("Map is not not_rectangular", STDOUT_FILENO);
	if (errors->walls == true)
		ft_putendl_fd("Map is not surrounded by walls", STDOUT_FILENO);
	if (errors->morecharacters == true)
		ft_putendl_fd("Map contains too many characters", STDOUT_FILENO);
}
