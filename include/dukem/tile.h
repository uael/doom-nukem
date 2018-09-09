/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dukem/tile.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUKEM_TILE_H
# define DUKEM_TILE_H

# include "dukem/vector.h"

struct s_renderer;
struct s_dukem;

/*
** All of the following content is pure speculation..
*/

/*
** Plan is flooring or ceiling
** `inc{x,y}` specify the angle on x and y
** `height` is the distance btw zero and the texture
** `texture` is the texture index
*/

typedef struct	s_plan
{
	uint8_t		incx;
	uint8_t		incy;
	uint8_t		height;
	uint8_t		texture;
}				t_plan;

/*
** Base of tile structure
** Only save floor and ceil since we always need theme
** `pump` update the tile
** `interact` interact with the tile
** `draw` draw the tile
*/

typedef struct	s_tile
{
	t_plan		floor;
	t_plan		ceil;

	void		(*pump)(struct s_dukem *game, struct s_tile *tile);
	void		(*interact)(struct s_dukem *game, struct s_tile *tile);
	void		(*draw)(struct s_dukem *game, struct s_tile *tile,
						struct s_renderer *renderer,
						t_vec3 origin);
}				t_tile;

/*
** A link tile, get 4 links and texture
*/

typedef struct	s_link
{
	t_tile		base;
	uint8_t		texture;
	uint8_t		padding[15];
	t_tile		*links[4];
}				t_link;

/*
** A doot tile, get 2 links, a texture and a opening percentage (decreased
** by pump after an interact ?)
*/

typedef struct	s_door
{
	t_tile		base;
	uint8_t		texture;
	uint8_t		open_pct;
	uint8_t		padding[14];
	t_tile		*links[2];
}				t_door;

typedef enum	e_tile_type
{
	TILE_LINK = 0,
	TILE_DOOR,
}				t_tile_type;

#endif
