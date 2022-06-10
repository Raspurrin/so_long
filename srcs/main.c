/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:10:46 by mialbert          #+#    #+#             */
/*   Updated: 2022/06/05 23:54:27 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		if (!(input_handler(fd, &data, &data.line)))
			return (EXIT_FAILURE);
	}
	else if (argc > 2)
		return (ft_putendl_fd("Error\nToo many arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	else
		return (ft_putendl_fd("Error\nNot enough arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	if (!graphics(&data, &data.line))
		free_2d(data.map);
	return (0);
}
