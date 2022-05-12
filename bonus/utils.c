/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:46:26 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/12 15:34:45 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

// int32_t	main(void)
// {
// 	int arr[] = {1, 40, 3};
// 	free_array(arr, "something was fucked");
// 	return (0);
// }