/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:10:46 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/10 03:02:18 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	exec_functions(t_imgdata *data)
{
	ssize_t	*avail;
	int		spawn_count;

	avail = avail_ground_spawn(data, &data->line, &spawn_count);
	if (!avail)
		return (false);
	if (!get_ground_spawn(&spawn_count, avail, data->enemy.pink_spawn, \
														PINKCOUNT))
		return (0);
	free(avail);
	get_ghost_spawn(data, &data->enemy, &data->line);
	if (!graphics(data, &data->line, &data->enemy))
		free_2d(data->map);
	return (true);
}

/**
 * Will receive a map as input and will have to determine whether the map
 * is valid or not and will then dynamically generate images based on the 
 * locations of everything provided in the map and proceed to run the game!
 */
int32_t	main(int32_t argc, char **argv)
{
	t_imgdata		data;
	int32_t			fd;

	ft_bzero(&data, sizeof(t_imgdata));
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_putendl_fd("Error\nInvalid file", STDOUT_FILENO) \
					, EXIT_FAILURE);
		if (!check_ext(argv[1], ".ber"))
			return (EXIT_FAILURE);
		if (!(input_handler(fd, &data, &data.line, &data.enemy)))
			return (EXIT_FAILURE);
	}
	else if (argc > 2)
		return (ft_putendl_fd("Error\nToo many arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	else
		return (ft_putendl_fd("Error\nNot enough arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	if (!(exec_functions(&data)))
		free_2d(data.map);
	return (0);
}
