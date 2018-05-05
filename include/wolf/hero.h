/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by nfinkel           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_HERO_H
# define WOLF3D_HERO_H

# include <libftx.h>

typedef struct		s_hero
{
    t_ln			fov;
    t_v2			where;
    t_v2			velocity;
    float 			speed;
    float 			acceleration;
    float 			theta;
}					t_hero;

extern void         init_hero(t_hero *hero, const float focal);

#endif