/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:59:12 by mialbert          #+#    #+#             */
/*   Updated: 2022/03/29 19:39:21 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if one line read contains the expected chararcters or not
 * @param line the line to be checked
 * @param check the string containing all expected characters
 * @return true if no characters from the check string have been found, otherwise false.
 */
static bool	error_check(char *line, char *check, int linecount, int size)
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
		else if (!(ft_strchr(check, line[i++])))
			return (false);
	}
	return (true);
}

char	**input_handler(void)
{
	int		fd;
	int		i;
	int		size;
	char	*line;
	char	**map;

	fd = open("map.ber", O_RDONLY);
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
			*map = malloc(size * sizeof(char));
			ft_strlcpy(map[i], line, size);
		}
		else
			return (NULL);
		error_check(line, "01CEP", i, size);
		i++;
	}
	i = -1; // to have a check for the last line
	error_check(line, "O1CEP", i, size);
	return (map);
}

int	main(int argc char **argv)
{

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