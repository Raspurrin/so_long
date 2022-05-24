/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:55:25 by mialbert          #+#    #+#             */
/*   Updated: 2022/05/23 20:23:27 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_enemy_error(t_imgdata *data, t_enemy *enemy, t_error errors)
{
	size_t			i;
	size_t			walls;

	i = 0;
	enemy->counts[0] = PINKCOUNT;
	enemy->counts[1] = GHOSTCOUNT;
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
/**
 *  
 * 
 * 
 * 
 * 
 * 
 * 
 */
// HOW ELSE WOULD YOU DO IT tf
// Because I have like an array of ghost images right? so at some point 
// I want to change to pink images (pink monsters)
// No I want them both at the same time
// THE THING IS
// that I want my functions to become dynamic and useable withdifferent enemies
// that is what I'm trying to fucking do
// Can you do this in a simple way then o-o
// stfu They are not pink ghosts. They are enemies that can only walk on the ground
// It already works with ghosts only
// But you probably think ... I'm stupid for doing this so complicated 
// But then can you think of a simple way then >__> 
// Yeah I could think of that myself
// I'm just saying that if you are gonna criticise then you should be able to 
// suggest something else. OTHER THAN RAGEQUITING
// I already have a spawn function for them and everything 
// .___. ._________. ._____________________.
// I know I am a retard. Brot? A baguette? No no no no no
/**
 * So I want to be able to itterate through ALL different enemies here,
 * but then I need to keep track at what point I need to change images, so I need to keep 
 * track when in the itteration I will use different enemies. Solution:
 * 
 * Initialise enemy.itter_index in a seperate function. 
 * For example: GHOSTCOUNT = 4 and PINKCOUNT = 2
 * Then enemy.itter_index will be: in32_t *array = {0, 4}
 * As for 0-4 I need to go through all ghost images and 4-6 I go through pink images. 
 * Then I need enemy->total_enemies to know where to stop itterating. 
 * And another array that holds the order of images I want to go through, like:
 * mlx_image_t *img_order = {ghost_img, pink_img} I don't think I can do this btw
 */