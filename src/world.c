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
			continue;
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

inline int		world_init(t_world *world, int ac, char *av[])
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

inline int		world_tile(t_world *world, uint8_t *tiles, t_v2 a)
{
	if (a.x > world->width || a.y > world->height)
		return 1;
	return ((int)tiles[((int)a.y * world->width) + (int)a.x]);
}

inline t_hit	world_cast(t_world *world, t_v2 where, t_v2 direction)
{
	t_v2 hor = v2_sh(where, direction);
	t_v2 ver = v2_sv(where, direction);
	t_v2 ray = v2_mag(v2_sub(hor, where)) < v2_mag(v2_sub(ver, where)) ? hor : ver;
	t_v2 dc = v2_mul(direction, 0.01f);
	t_v2 dx = { dc.x, 0.0f };
	t_v2 dy = { 0.0f, dc.y };
	t_v2 test = v2_add(ray, v2_mag(v2_sub(hor, ver)) < 1e-3f ? dc :
							math_dec(ray.x) == 0.0f ? dx : dy);
	const t_hit hit = {world_tile(world, world->wall, test), ray };
	return (hit.tile ? hit : world_cast(world, ray, direction));
}
