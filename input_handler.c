/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:59:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/03/30 20:15:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./libft/srcs/libft.h"

char	*display_error(char **map)
{
	int32_t	i;

	i = 0;
	ft_putendl_fd("Error\n", STDOUT_FILENO);
	while (*map)
	{
		free(*map);
		map++;
	}
	return (NULL);
}

/**
 * @brief Checks if one line read contains the expected chararcters or not
 * @param line The line to be checked
 * @param check The string containing all expected characters
 * @return True if no characters from the check string have been found, 
 * otherwise false.
 */
static bool	error_check(char *line, int32_t linecount, int32_t size,
						struct s_checks checks)
{
	int32_t	i;

	i = 0;
	if (linecount <= 0 && !(ft_strchr(line, '1')))
		return (ft_putendl_fd("Error\n", STDOUT_FILENO), false);
	else
		return (true);
	if (i == 0 || i == size - 1)
	{
		if (line[i] != '1')
			return (ft_putendl_fd("Error\n", STDOUT_FILENO), false);
	}
	else if (!(ft_strchr("01CEP", line[i++])))
		return (ft_putendl_fd("Error\n", STDOUT_FILENO), false);
	else if (ft_strchr(line, 'C'))
		checks.collectible++;
	else if (ft_strchr(line, 'P'))
		checks.start++;
	else if (ft_strchr(line, 'E'))
		checks.exit++;
	return (true);
}

char	**input_handler(int32_t fd, struct s_checks checks, char **map)
{
	size_t				i;
	size_t				size;
	char				*line;

	size = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = malloc(i * sizeof(char *));
		if (i == 0 || (i > 1 && ft_strlen(line) == size))
		{
			size = ft_strlen(line);
			ft_strlcpy(map[i], line, size);
		}
		else
			return (NULL);
		if (!(error_check(line, i, size, checks)))
			display_error(map);
		i++;
	}
	error_check(line, -1, size, checks);
	return (map);
}

int32_t	main(int32_t argc, char **argv)
{
	char			**map;
	int32_t			fd;
	struct s_checks	checks;

	map = NULL;
	checks.collectible = 0;
	checks.exit = 0;
	checks.start = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putendl_fd("Error\n Invalid file\n", STDOUT_FILENO);
			return (EXIT_FAILURE);
		}
		input_handler(fd, checks, map);
		if (!(checks.collectible >= 1 && checks.exit >= 1 && checks.start >= 1))
			display_error(map);
	}
	return (0);
}

/**
 *  
 * Determine length of 2D array first, so it can be malloced
 * First you check amount of lines and then length of lines
 * if lines aren't all the same size, then return error
 * 
 * BUT you have to read it in order to get this information
 * Which means you have to store the information before knowing
 * the length? Perhaps adjust length and malloc every time? 
 * Seems inefficient
 * 
 * Oorr... Put it in a linked list, so you don't need to know the length
 * Don't know how to do that though
 * 
 * Have to make sure size will contain previous line value at first
 * Which is why line is first evaluated from strlen before being put
 * into the size variable
 * 
 * checking i to make sure one line has been read before
 * making comparisons in the if statement
 * 
 * Strjoin everything into one big string and then ft_split
 * Just... Read everything? And then split. Array size problem possibly
 * First count amount of lines before mallocing
 * Linked lists
 */