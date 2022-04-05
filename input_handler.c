/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:59:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/05 19:05:29 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./libft/srcs/libft.h"
#include <stdio.h>

/**
 * @brief Checks if a file name contains the right extension.
 * @param file_name The file name to be checked.
 * @param ext The extension it should have.
 * @return true if it contains the requested extension, otherwise false.
 */
static bool	check_ext(char *file_name, char *ext)
{
	size_t	ext_len;
	size_t	name_len;

	if (!ext)
		return (ft_putendl_fd("Error\nYou are not checking for an extension", \
				STDOUT_FILENO), false);
	if (!file_name)
		return (ft_putendl_fd("Error\nThere is no file name", \
				STDOUT_FILENO), false);
	ext_len = ft_strlen(ext);
	name_len = ft_strlen(file_name);
	while (ext_len > 0)
	{
		if (file_name[name_len--] != ext[ext_len--])
			return (ft_putendl_fd("Error\nWrong file extension", \
					STDOUT_FILENO), false);
	}
	return (true);
}

/**
 * @brief Checks if the map contains walls.
 * @param map The 2D array containing the map.
 * @param linecount Amount of lines in the map.
 * @param size Size of the lines.
 * @param checks Counters for the elements of the map.
 * @return True if it passes all error checks, otherwise false.
 */
static bool	check_walls(char **map, int32_t linecount, size_t linesize)
{
	size_t	i;

	i = 0;
	ft_strchr(map[linecount], '1');
	while (i < linesize)
	{
		if (map[0][i] != '1' || map[linecount][i++] != '1')
			return (ft_putendl_fd("Error\nMap is not surrounded by walls", \
					STDOUT_FILENO), false);
	}
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][linesize - 1] != '1')
			return (ft_putendl_fd("Error\nMap is not surrounded by walls", \
					STDOUT_FILENO), false);
		i++;
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
		return (ft_putendl_fd("Error\nDoes not contain at least 1 collectible, \
				map exit and starting position", STDOUT_FILENO), false);
	while (line[i])
	{
		if (!(ft_strchr("01CEP\n", line[i++])))
			return (ft_putendl_fd("Error\nContains input other than 01CEP", \
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
	while (map[i + 1])
	{
		*linesize = ft_strlen(map[i++]);
		if (*linesize != ft_strlen(map[i]))
			return (ft_putendl_fd("Error\nMap is not rectangular", \
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
	buf = malloc(5000 * sizeof(char));
	while (buflen == 5000)
	{
		buflen = read(fd, buf, 5000);
		if (buflen <= 0)
			return (free (line), NULL);
		line = malloc(buflen * sizeof(char));
		line = gnl_strjoin(line, buf);
	}
	free(buf);
	map = ft_split(((const char *)line), '\n');
	if (!map)
		return (ft_putendl_fd("Error\nInvalid map", STDOUT_FILENO), NULL);
	linecount = check_if_rectangular(map, &linesize);
	if (!(check_cases(line)) || !(check_walls(map, linecount, linesize) \
		|| linecount == 0))
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
			return (ft_putendl_fd("Error\n Invalid file", STDOUT_FILENO) \
					, EXIT_FAILURE);
		if (!check_ext(argv[1], ".ber"))
			return (EXIT_FAILURE);
		input_handler(fd, map);
	}
	else if (argc > 2)
		return (ft_putendl_fd("Error\nToo many arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	else
		return (ft_putendl_fd("Error\nNot enough arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
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