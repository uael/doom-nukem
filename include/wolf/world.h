/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf/world.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_WORLD_H
# define WOLF_WORLD_H

# include "wolf/math.h"

# define HDR_SZ   (6)
# define TILE_SZ  (2)
# define TILE_MAX (45)

typedef struct	s_world
{
	uint8_t		width;
	uint8_t		height;
	uint8_t		*floor;
	uint8_t		*wall;
	uint8_t		*ceil;
}				t_world;

extern int		world_init(t_world *world, int ac, char *av[]);
extern int		world_tile(t_world *world, uint8_t *tiles, t_v2 a);
extern int		world_cast(t_hit *hiy, t_world *world, t_v2 where, t_v2 dir);

#endif
