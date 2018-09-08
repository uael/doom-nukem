/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf/me.h"

#include <SDL2/SDL.h>

static inline int	find_start(t_v2 *start, t_world *world)
{
	start->x = -1.5f;
	while ((start->x += 1.f) < world->width)
	{
		start->y = -1.5f;
		while ((start->y += 1.f) < world->height)
		{
			if (!world_tile(world, world->wall, *start)
				&& world_tile(world, world->floor, *start)
				&& world_tile(world, world->ceil, *start))
				return (0);
		}
	}
	return (-1);
}

inline int			me_init(t_me *me, t_world *world, const float focal)
{
	t_v2 pos;

	if (find_start(&pos, world))
		return (-1);
	*me = (t_me){
		{ { focal, -1.0f }, { focal, +1.0f } },
		pos,
		{ 0.0f, 0.0f },
		0.10f,
		0.015f,
		0.0f
	};
	return (0);
}

/*
** Prevent collision and perform wall sliding
** If the new position collide a wall in a range of .3f:
**  - calculate the hit positions
**  - cancel player velocity on collided axes
**  - reduce un-collided axes velocity by 5%
*/

static inline void	collide_or_move(t_me *me, t_world *world)
{
	t_v2	last;
	t_hit	hits[4];
	int		count;
	int		i;

	last = me->where;
	me->where = v2_add(me->where, me->velocity);
	if ((count = world_hit(world, me->where, 0.2f, hits)))
	{
		i = -1;
		while (++i < count)
			if (hits[i].hor)
			{
				me->where.x = hits[i].where.x - .21f;
				me->velocity.x = .0f;
				me->velocity.y *= .95f;
			}
			else
			{
				me->velocity.y = hits[i].where.y - .21f;
				me->velocity.y = .0f;
				me->velocity.x *= .95f;
			}
		me->where = v2_add(last, me->velocity);
	}
}

inline void			me_move(t_me *me, t_world *world, const uint8_t *keys)
{
	t_v2 acc;

	if (keys[SDL_SCANCODE_LEFT])
		me->theta -= 0.1f;
	if (keys[SDL_SCANCODE_RIGHT])
		me->theta += 0.1f;
	if (!keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S] &&
		!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A])
		me->velocity = v2_mul(me->velocity, 1.0f - me->accel / me->speed);
	else
	{
		acc = (t_v2){ 1.0f, 0.0f };
		acc = v2_mul(v2_turn(acc, me->theta), me->accel);
		if (keys[SDL_SCANCODE_W])
			me->velocity = v2_add(me->velocity, acc);
		if (keys[SDL_SCANCODE_S])
			me->velocity = v2_sub(me->velocity, acc);
		if (keys[SDL_SCANCODE_D])
			me->velocity = v2_add(me->velocity, v2_rag(acc));
		if (keys[SDL_SCANCODE_A])
			me->velocity = v2_sub(me->velocity, v2_rag(acc));
	}
	if (v2_mag(me->velocity) > me->speed)
		me->velocity = v2_mul(v2_unit(me->velocity), me->speed);
	collide_or_move(me, world);
}
