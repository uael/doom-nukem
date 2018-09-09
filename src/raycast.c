/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/09/09 11:45:56 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf/world.h"

inline int			world_tile(t_world *world, uint8_t *tiles, t_v2 a)
{
	if (a.x > world->width || a.y > world->height)
		return (1);
	return ((int)tiles[((int)a.y * world->width) + (int)a.x]);
}

static int			hit_ray(t_hit *hit, t_world *world, t_v2 dir, t_v2 ray)
{
	t_v2	dc;
	t_v2	test;

	dc = v2_mul(dir, 0.01f);
	if (hit->step < 1e-3f)
		test = v2_add(ray, dc);
	else if ((hit->hor = (math_dec(ray.x) == 0.0f)))
		test = v2_add(ray, (t_v2){ dc.x, 0.0f });
	else
		test = v2_add(ray, (t_v2){ 0.0f, dc.y });
	if ((hit->tile = world_tile(world, world->wall, test)))
	{
		hit->where = ray;
		return (1);
	}
	return (world_cast(hit, world, ray, dir));
}

inline int			world_cast(t_hit *hit, t_world *world, t_v2 where, t_v2 dir)
{
	t_v2	hor_step;
	t_v2	ver_step;
	t_v2	ray;

	hor_step = v2_steps_hor(where, dir);
	ver_step = v2_steps_ver(where, dir);
	ray = v2_mag(v2_sub(hor_step, where)) < v2_mag(v2_sub(ver_step, where))
		? hor_step : ver_step;
	hit->step = v2_mag(v2_sub(hor_step, ver_step));
	return (hit_ray(hit, world, dir, ray));
}

inline int			world_hit(t_world *world, t_v2 start, float range, t_hit *h)
{
	int		count;
	int		x;
	int		y;
	t_v2	dir;

	count = 0;
	x = -2;
	while (++x <= 1 && count < 4)
	{
		y = -2;
		while (++y <= 1 && count < 4)
			if (x || y)
			{
				dir = (t_v2){ start.x + (range * x), start.y + (range * y) };
				if (world_tile(world, world->wall, dir))
					world_cast(h + count++, world, start, (t_v2){ x, y });
			}
	}
	return (count);
}
