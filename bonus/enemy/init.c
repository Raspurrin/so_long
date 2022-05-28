/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:55:25 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/28 03:59:36 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	enemy_init(t_enemy *enemy)
{
	enemy->move[0] = enemy->ghost_move;
	enemy->move[1] = enemy->pink_move;
	enemy->move[2] = NULL;
	enemy->excep[0] = enemy->ghost_excep;
	enemy->excep[1] = enemy->pink_excep;
	enemy->excep[2] = NULL;
	enemy->counts[0] = GHOSTCOUNT;
	enemy->counts[1] = PINKCOUNT;
	enemy->pink_anim.length = 120;
	enemy->pink_anim.xy[1] = 0;
	enemy->pink_anim.xy[0] = 0;
	enemy->pink_anim.dir = PINK_R;
}

void	check_enemy_error(t_imgdata *data, t_enemy *enemy, \
											t_error errors)
{
	size_t			i;
	size_t			walls;

	i = 0;
	enemy_init(enemy);
	while (enemy->counts[i] != 0)
		enemy->total_enemies += enemy->counts[i++];
	if (DIFFCOUNT != i)
		errors.wrong_diffcount = true;
	walls = getncount(data->bigass, '1');
	enemy->max = ((data->line.size) * (data->line.count + 1)) \
									- (data->collect + 2 + walls);
	if (enemy->total_enemies > enemy->max)
		errors.enemyoverflow = true;
	if (GHOSTCOUNT < 1 || PINKCOUNT < 1)
		errors.enemyunderflow = true;
}
