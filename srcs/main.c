/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:10:46 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/20 16:08:36 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "MLX42.h"

int32_t	main(int32_t argc, char **argv)
{
	t_imgdata		data;
	int32_t			fd;

	ft_bzero(&data, sizeof(t_imgdata));
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_putendl_fd("Error\n Invalid file", STDOUT_FILENO) \
					, EXIT_FAILURE);
		if (!check_ext(argv[1], ".ber"))
			return (EXIT_FAILURE);
		if (!(input_handler(fd, &data, &data.line)))
			return (0);
	}
	else if (argc > 2)
		return (ft_putendl_fd("Error\nToo many arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	else
		return (ft_putendl_fd("Error\nNot enough arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	get_enemy_spawn(&data);
	graphics(&data, &data.line);
	return (0);
}
