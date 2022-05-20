/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:20:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/20 05:25:02 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/**
 * Reads the map into one big ass string directly with the read 
 * function instead of GNL to avoid memory fuckery and having it 
 * initialised instead of reading repeatedly is more efficient.
 * Later on store it in a 2D array for easy error checking
 * and data checking during the game loop. 
 */
char	*read_file(int32_t fd)
{
	int32_t	buflen;
	char	*line;
	char	*buf;

	buflen = 1;
	line = ft_calloc(1, 1);
	buf = malloc(BUFFERSIZE + 1 * sizeof(char));
	while (buflen > 0)
	{
		buflen = read(fd, buf, BUFFERSIZE);
		if (buflen <= 0)
			free (buf);
		if (buflen == 0)
			return (line);
		if (buflen < 0)
			return (NULL);
		buf[buflen] = '\0';
		line = gnl_strjoin(line, buf);
	}
	return (line);
}
