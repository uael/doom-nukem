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

# include "wolf/math.h"

typedef struct	s_me
{
	t_line		fov;
	t_v2		where;
	t_v2		velocity;
	double		speed;
	double		accel;
	double		theta;
}				t_me;

/*
** Initialize the player structure
** @param me    The player
** @param pos   Initial player position
** @param focal Player FOV focal
*/
extern void		me_init(t_me *me, t_v2 pos, double focal);
/*
** Move the player based on the keyboard state
** @param me   The player
** @param wall Walling data
** @param keys Keyboard state
*/
extern void		me_move(t_me *me, const char **wall, const uint8_t *keys);

#endif
