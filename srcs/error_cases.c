/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:09:44 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/12 20:07:52 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*read_file(int32_t fd)
{
	char	*bigass;

	bigass = ft_calloc(500, 1);
	read(fd, bigass, 500);
	return (bigass);
}

// char	*read_file(int32_t fd)
// {
// 	char	*buf;
// 	char	*bigass;

// 	bigass = malloc(1);
// 	bigass[0] = '\0';
// 	while (1)
// 	{
// 		buf = get_next_line(fd);
// 		if (!buf)
// 			break ;
// 		bigass = gnl_strjoin(bigass, buf);
// 	}
// 	return (bigass);
// }
	// int32_t				buflen;
	// char				*buf;
	// int					i;

	// buflen = 500;
	// buf = malloc(501 * sizeof(char));
	// i = 1;
	// while (buflen == 500)
	// {
	// 	buflen = read(fd, buf, 500);
	// 	if (buflen <= 0 && *line)
	// 		return (free (line), NULL);
	// 	buf[buflen] = '\0';
	// 	line = malloc((buflen * i++) * sizeof(char));
	// 	line = gnl_strjoin(line, buf);
	// }
	// free (buf);
	// return (line);

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
