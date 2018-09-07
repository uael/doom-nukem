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

inline void			me_init(t_me *me, t_v2 pos, const float focal)
{
	*me = (t_me){
		{ { focal, -1.0f }, { focal, +1.0f } },
		pos,
		{ 0.0f, 0.0f },
		0.15f,
		0.015f,
		0.0f
	};
}

/*
** Prevent collision and perform wall sliding
** If the new position collide a wall:
**  - calculate the hit position
**  - cancel player velocity on collided axes
**  - reduce un-collided axes velocity by 5%
**  - If we still collide, keep calm, stay in place, don't SEGFAULT..
*/

static inline void	collide_or_move(t_me *me, t_world *world)
{
	t_v2	last;
	t_hit	hit;

	last = me->where;
	me->where = v2_add(me->where, me->velocity);
	if (world_tile(world, world->wall, me->where))
	{

		hit = world_cast(world, last, me->velocity);
		if (math_isfl(hit.where.x))
		{
			me->velocity.x = 0.0;
			me->velocity.y *= 0.95;
		}
		if (math_isfl(hit.where.y))
		{
			me->velocity.y = 0.0;
			me->velocity.x *= 0.95;
		}
		me->where = v2_add(last, me->velocity);
		if (world_tile(world, world->wall, me->where))
		{
			me->velocity = (t_v2){ 0.0, 0.0 };
			me->where = last;
		}
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
