/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:59:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/03/29 22:04:58 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_error(char **map)
{
	int32_t	i;

	i = 0;
	ft_printf("Error\n");
	while (*map)
	{
		free(*map);
		*map++;
	}
	return (NULL);
}

/**
 * @brief Checks if one line read contains the expected chararcters or not
 * @param line the line to be checked
 * @param check the string containing all expected characters
 * @return true if no characters from the check string have been found, 
 * otherwise false.
 */
static bool	error_check(char *line, int linecount, int size,
						struct s_checks checks)
{
	int32_t	i;

	i = 0;
	if (linecount <= 0 && !(ft_strchr(line, '1')))
		return (false);
	else
		return (true);
	while (line[i])
	{
		if (i == 0 || i == size - 1)
		{
			if (line[i] != '1')
				return (false);
		}
		else if (!(ft_strchr("01CEP", line[i++])))
			return (false);
		else if (ft_strchr(line[i], 'C'))
			checks.collectible++;
		else if (ft_strchr(line[i], 'P'))
			checks.start++;
		else if (ft_strchr(line[i], 'E'))
			checks.exit++;
	}
	return (true);
}

char	**input_handler(int fd, struct s_checks checks, char **map)
{
	int				i;
	int				size;
	char			*line;

	size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = malloc(i * sizeof(char *));
		if (i == 0 || i > 1 && ft_strlen(line) == size)
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

int	main(int argc, char **argv)
{
	char			**map;
	int				fd;
	struct s_checks	checks;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
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
 */

/**
 * Have to make sure size will contain previous line value at first
 * Which is why line is first evaluated from strlen before being put
 * into the size variable
 * 
 * checking i to make sure one line has been read before
 * making comparisons in the if statement
 */