/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dukem/level.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUKEM_LEVEL_H
# define DUKEM_LEVEL_H

# include "dukem/tile.h"

/*
** We only need to known where to start since all tile have to be connected..
** Save end for now, TODO
*/

typedef struct	s_level
{
	t_tile		*start;
	t_tile		*end;
}				t_level;

/*
** Read & write a level from file,
** the binary have the following format:
** | Level length   2 bytes
** | Tiles length   2 bytes
** | Tile           n byte(s)
**   | Tile kind    1 byte
**   | Tile data    x byte(s) TODO
**   | Links count  1 byte
**   | Links        n byte(s)
**     | Tile index 1 byte
**     ..
**   ..
*/

extern int		level_read(t_level *level, const char *file);
extern int		level_write(const t_level *level, const char *file);

#endif
