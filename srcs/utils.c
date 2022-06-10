/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:46:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/05 23:45:30 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_2d(char **map)
{
	while (*map)
	{
		free(*map);
		map++;
	}
	return ;
}

bool	free_array(mlx_image_t **arr, char *str, t_imgdata *data)
{
	ft_putendl_fd("Error", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	while (arr)
	{
		free(arr);
		arr++;
	}
	free_2d(data->map);
	return (false);
}

void	error_close_window(t_imgdata *data, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	terminate(data);
}

void	free_close_window(t_imgdata *data, void *var, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	free(var);
	terminate(data);
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
