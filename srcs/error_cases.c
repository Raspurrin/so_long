/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:09:44 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/11 15:19:05 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_file(int32_t fd, char *line)
{
	int32_t				buflen;
	char				*buf;

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
	return (line);
}

void	error_output(t_error *errors, t_line *line)
{
	if (errors->cpe == true || errors->different_input == true \
		|| errors->file_name == true || errors->rectangular == true \
		|| errors->walls == true || errors->morecharacters == true \
		|| line->count == 0)
	{
		errors->error = true;
		ft_putendl_fd("Error", STDOUT_FILENO);
	}
	if (errors->cpe == true)
		ft_putendl_fd("Does not contain at least 1 collectible, \
map exit and starting position", STDOUT_FILENO);
	if (errors->different_input == true)
		ft_putendl_fd("Contains input other than 01CEP", STDOUT_FILENO);
	if (errors->rectangular == true)
		ft_putendl_fd("Map is not rectangular", STDOUT_FILENO);
	if (errors->walls == true)
		ft_putendl_fd("Map is not surrounded by walls", STDOUT_FILENO);
	if (errors->morecharacters == true)
		ft_putendl_fd("Map contains too many characters", STDOUT_FILENO);
	return ;
}
