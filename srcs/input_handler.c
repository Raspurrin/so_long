/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:59:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/11 15:38:52 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if a file name contains the right extension.
 * @param file_name The file name to be checked.
 * @param ext The extension it should have.
 * @return true if it contains the requested extension, otherwise false.
 */
bool	check_ext(char *file_name, char *ext)
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
static bool	check_walls(char **map, t_line *line, \
						t_error *errors)
{
	size_t	i;

	i = 0;
	ft_strchr(map[line->count], '1');
	while (i < line->size)
	{
		if (map[0][i] != '1' || map[line->count][i++] != '1')
			return (errors->walls = true, false);
	}
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][line->size - 1] != '1')
			return (errors->walls = true, false);
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
static bool	check_cases(char *line, t_error *errors)
{
	size_t	i;
	char	*foundchar;

	i = 0;
	foundchar = ft_strchr(line, 'P') + 1;
	if (foundchar)
	{
		if (ft_strchr(foundchar, 'P'))
			errors->morecharacters = true;
	}
	if (!(ft_strchr(line, 'C')) || !(ft_strchr(line, 'P')) \
	|| !(ft_strchr(line, 'E')))
		errors->cpe = true;
	while (line[i])
	{
		if (!(ft_strchr("01CEP\n", line[i++])))
			errors->different_input = true;
	}
	if (errors->cpe == true || errors->different_input == true)
		return (false);
	return (true);
}

/**
 * @brief Checks if every line is the same size in the map.
 * @param map The map.
 * @return Amount of lines in the map.
 */
static size_t	check_if_rectangular(char **map, t_line *line, \
									t_error *errors)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (map[i + 1]) // it not work so function returns nothing
	{
		line->size = ft_strlen(map[i++]);
		if (line->size != ft_strlen(map[i]))
			errors->rectangular = true;
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
char	**input_handler(int32_t fd, char ***map, t_line *line)
{
	char				*bigass;
	t_error				errors;

	bigass = NULL;
	ft_bzero(&errors, sizeof(t_error));
	bigass = read_file(fd, bigass);
	*map = ft_split(((const char *)bigass), '\n');
	if (!*map)
		return (ft_putendl_fd("Error\nInvalid map", STDOUT_FILENO), NULL);
	line->count = check_if_rectangular(*map, line, &errors);
	check_cases(bigass, &errors);
	check_walls(*map, line, &errors);
	error_output(&errors, line);
	if (errors.error == true)
		return (free_2d(*map), NULL);
	return (*map);
}
