/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:59:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/17 00:15:52 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
static bool	check_cases(t_error *errors, t_imgdata *data)
{
	size_t	i;

	i = 0;
	check_player_amount(errors, data);
	if (!(ft_strchr(data->bigass, 'C')) || !(ft_strchr(data->bigass, 'P')) \
	|| !(ft_strchr(data->bigass, 'E')))
		errors->no_cpe = true;
	while (data->bigass[i])
	{
		if (data->bigass[i] == 'C')
			data->collect++;
		if (!(ft_strchr("01CEP\n", data->bigass[i++])))
			errors->different_input = true;
	}
	if (errors->no_cpe == true || errors->different_input == true)
		return (false);
	return (true);
}

/**
 * @brief Checks if every line is the same size in the map.
 * @param map The map.
 * @return Amount of lines in the map.
 */
static size_t	check_if_not_rectangular(char **map, t_line *line, \
									t_error *errors)
{
	size_t	i;

	i = 0;
	while (map[i + 1])
	{
		line->size = ft_strlen(map[i++]);
		if (line->size != ft_strlen(map[i]))
			errors->not_rectangular = true;
	}
	line->count = ft_strlen(map[i]);
	if (line->size == i)
		errors->not_rectangular = true;
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
char	**input_handler(int32_t fd, t_imgdata *data, t_line *line, \
													t_enemy *enemy)
{
	t_error	errors;
	size_t	walls;

	ft_bzero(&errors, sizeof(t_error));
	data->bigass = read_file(fd);
	data->map = ft_split(((const char *)data->bigass), '\n');
	if (!data->map)
		return (ft_putendl_fd("Error\nInvalid map", STDOUT_FILENO), NULL);
	line->count = check_if_not_rectangular(data->map, line, &errors);
	walls = getncount(data->bigass, '1');
	enemy->max = ((data->line.size) * (data->line.count + 1)) \
									- (data->collect + 2 + walls);
	if (GHOSTCOUNT > enemy->max)
		errors.enemyoverflow = true;
	if (GHOSTCOUNT < 1)
		errors.enemyunderflow = true;
	check_cases(&errors, data);
	check_walls(data->map, line, &errors);
	error_output(&errors, line);
	if (errors.error == true)
		return (free_2d(data->map), NULL);
	return (data->map);
}
