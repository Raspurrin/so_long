/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:20:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/29 03:21:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*read_file(int32_t fd)
{
	int32_t	buflen;
	char	*line;
	char	*buf;
	int		i;

	buflen = 1;
	line = ft_calloc(1, 1);
	buf = malloc(500 + 1 * sizeof(char));
	i = 1;
	while (buflen > 0)
	{
		buflen = read(fd, buf, 500);
		// if (buflen < 0)
		// {
		// 	free (line);
		// 	free (buf);
		// 	return (NULL);
		// }
		buf[buflen] = '\0';
		line = gnl_strjoin(line, buf);
	}
	return (line);
}
