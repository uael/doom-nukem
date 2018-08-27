/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf/me.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_ME_H
# define WOLF_ME_H

# include "wolf/world.h"

typedef struct	s_me
{
	t_line		fov;
	t_v2		where;
	t_v2		velocity;
	float		speed;
	float		accel;
	float		theta;
}				t_me;

/*
** Initialize the player structure
** @param me    The player
** @param pos   Initial player position
** @param focal Player FOV focal
*/
extern void		me_init(t_me *me, t_v2 pos, float focal);
/*
** Move the player based on the keyboard state
** @param me   The player
** @param wall Walling data
** @param keys Keyboard state
*/
extern void		me_move(t_me *me, t_world *world, const uint8_t *keys);

#endif
