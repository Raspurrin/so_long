/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:46:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/28 05:43:40 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

bool	free_array(void *arr, char *str)
{
	char	*arr2;

	arr2 = (char *)arr;
	ft_putendl_fd("Error", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	while (arr)
	{
		free(arr);
		arr++;
	}
	return (false);
}

void	error_close_window(t_imgdata *data, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	mlx_close_window(data->mlx);
	kill(0, SIGKILL);
}

void	free_close_window(t_imgdata *data, void *var, char *str)
{
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	free(var);
	mlx_close_window(data->mlx);
	kill(0, SIGKILL);
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
