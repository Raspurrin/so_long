/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:59:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/04 21:17:46 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./libft/srcs/libft.h"

/**
 * @brief Checks if the map contains walls.
 * @param map The 2D array containing the map.
 * @param linecount Amount of lines in the map.
 * @param size Size of the lines.
 * @param checks Counters for the elements of the map.
 * @return True if it passes all error checks, otherwise false.
 */
static bool	check_walls(char **map, int32_t linecount, int32_t linesize)
{
	int32_t	i;

	i = 0;
	if (!(ft_strchr(map[1], '1')) || !(ft_strchr(map[linecount], '1')))
		return (ft_putendl_fd("Error\n Map is not surrounded by walls", \
				STDOUT_FILENO), false);
	while (*map)
	{
		if (*map[1] != '1' || *map[linesize] != '1')
			return (ft_putendl_fd("Error\n Map is not surrounded by walls", \
					STDOUT_FILENO), false);
		*map++;	// expression result unused ??? 
	}
	return (true);
}

/**
 * @brief Checks if the map only contains the appropiate characters or not
 * and if it contains at least one exit, collectible and starting position.
 * 0: Empty space, 1:  wall, C: collectible, E: map exit, P: starting pos.
 * @param line One big string containing the entire map.
 * @param checks Struct to take track of the elements of the map.
 * @return True if it passes all error checks, otherwise false.
 */
static bool	check_cases(char *line)
{
	size_t	i;

	i = 0;
	if (!(ft_strchr(line, 'C')) || !(ft_strchr(line, 'P')) \
	|| !(ft_strchr(line, 'E')))
		return (ft_putendl_fd("Error\n Does not contain at least 1 collectible, \
				map exit and starting position", STDOUT_FILENO), false);
	while (line[i])
	{
		if (!(ft_strchr("01CEP", line[i++])))
			return (ft_putendl_fd("Error\n Contains input other than 01CEP", \
					STDOUT_FILENO), false);
	}
	return (true);
}

/**
 * @brief Checks if every line is the same size in the map.
 * @param map The map.
 * @return Amount of lines in the map.
 */
static size_t	check_if_rectangular(char **map, size_t *linesize)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (map[i])
	{
		*linesize = ft_strlen(map[i++]);
		if (*linesize != ft_strlen(map[i]))
			return (ft_putendl_fd("Error\n Map is not rectangular", \
					STDOUT_FILENO), false);
	}
	return (i);
}

/**
 * @brief Reads the lines of the map. Both using one big string
 * and a 2D array to check for different error cases in other functions.
 * @param fd The file descriptor to be read from.
 * @param checks Struct containing the different elements of the map.
 * @param map The 2D array that will eventually contain the input. 
 * @return The map in a 2D array.
 */
static char	**input_handler(int32_t fd, char **map)
{
	size_t				linesize;
	size_t				linecount;
	int32_t				buflen;
	char				*buf;
	char				*line;

	buflen = 5000;
	buf = NULL;
	line = NULL;
	while (buflen == 5000)
	{
		buflen = read(fd, buf, 5000);
		if (buflen <= 0)
			return (free (line), NULL);
		line = malloc(buflen * sizeof(char));
		line = gnl_strjoin(line, buf);
	}
	map = ft_split(((const char *)line), '\n');
	if (!(check_cases(line)))
		free_2d(map);
	linecount = check_if_rectangular(map, &linesize);
	if (!(check_walls(map, linecount, linesize)))
		free_2d(map);
	return (map);
}

int32_t	main(int32_t argc, char **argv)
{
	char			**map;
	int32_t			fd;

	map = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_putendl_fd("Error\n Invalid file\n", STDOUT_FILENO) \
					, EXIT_FAILURE);
		input_handler(fd, map);
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
 * 
 * Option 1:
 * First read line by line using get_next_line to get the number of lines
 * And *then* malloc appropiate number of pointers and initialize everything
 * 
 * OR 
 * 
 * Option 2:
 * get everything into one big string, use ft_split and then go through the outer
 * elements to count the size
 */

// just in case: