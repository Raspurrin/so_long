/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:09:20 by mialbert          #+#    #+#             */
/*   Updated: 2022/04/29 03:21:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include "../test/includes/so_long_bonus.h"
#include "../test/libs/libft/srcs/libft.h"

int32_t	main(void)
{
	t_error	errors[5];
	int32_t	i;

	i = 0;

	while (i < 5)
		ft_bzero(&errors[i++], sizeof(t_error));
	return (0);
}
