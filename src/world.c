/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf/world.h"

#include <fcntl.h>
#include <unistd.h>

#define HDR_SZ   6
#define TILE_SZ  2
#define TILE_MAX 45

static inline int	compress(t_world *world, uint8_t *buf)
{
	uint8_t		*it;
	uint16_t	i;
	uint16_t	sz;

	i = 0;
	sz = (uint16_t)(world->width * world->height * 3);
	it = buf;
	while (i < sz)
	{
		if (*it == '\n')
		{
			++it;
			continue ;
		}
		if (it[0] == ' ')
			it[0] = '0';
		if (it[1] == ' ')
			it[1] = '0';
		if (!ft_isdigit(*it) || !ft_isdigit(it[1]))
			return (-1);
		buf[i++] = (uint8_t)(((it[0] - '0') * 10) + it[1] - '0');
		it += 2;
	}
	return (0);
}

inline int			world_init(t_world *world, int ac, char *av[])
{
	int				fd;
	static uint8_t	buf[(((TILE_MAX * TILE_SZ) + 1) * TILE_MAX * 3) + 3];
	ssize_t			desired;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	if (read(fd, buf, HDR_SZ) != HDR_SZ)
		return (-1);
	if (!ft_isdigit(buf[0]) || !ft_isdigit(buf[1]) || buf[2] != ':')
		return (close(fd) | -1);
	world->width = (uint8_t)(((buf[0] - '0') * 10) + buf[1] - '0');
	if (!ft_isdigit(buf[3]) || !ft_isdigit(buf[4]) || buf[5] != '\n')
		return (close(fd) | -1);
	world->height = (uint8_t)(((buf[3] - '0') * 10) + buf[4] - '0');
	desired = (((world->width * TILE_SZ) + 1) * world->height * 3) + 2;
	if (read(fd, buf, (size_t)desired + 1) != desired || compress(world, buf))
		return (close(fd) | -1);
	world->floor = buf;
	world->wall = world->floor + (world->width * world->height);
	world->ceil = world->wall + (world->width * world->height);
	return (close(fd));
}

inline int			world_tile(t_world *world, uint8_t *tiles, t_v2 a)
{
	if (a.x > world->width || a.y > world->height)
		return (1);
	return ((int)tiles[((int)a.y * world->width) + (int)a.x]);
}

static t_hit		hit_ray(t_world *world, t_v2 dir, t_v2 ray, float step)
{
	t_v2	dc;
	t_v2	test;
	t_hit	hit;

	dc = v2_mul(dir, 0.01f);
	if (step < 1e-3f)
		test = v2_add(ray, dc);
	else if (math_dec(ray.x) == 0.0f)
	{
		hit.hor = 1;
		test = v2_add(ray, (t_v2){ dc.x, 0.0f });
	}
	else
	{
		hit.hor = 0;
		test = v2_add(ray, (t_v2){ 0.0f, dc.y });
	}
	if (!(hit.tile = world_tile(world, world->wall, test)))
		return (world_cast(world, ray, dir));
	hit.where = ray;
	return (hit);
}

inline t_hit		world_cast(t_world *world, t_v2 where, t_v2 dir)
{
	t_v2	hor_step;
	t_v2	ver_step;
	t_v2	ray;

	hor_step = v2_steps_hor(where, dir);
	ver_step = v2_steps_ver(where, dir);
	ray = v2_mag(v2_sub(hor_step, where)) < v2_mag(v2_sub(ver_step, where))
		? hor_step : ver_step;
	return (hit_ray(world, dir, ray, v2_mag(v2_sub(hor_step, ver_step))));
}
