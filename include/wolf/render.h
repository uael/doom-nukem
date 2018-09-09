/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf/render.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_RENDER_H
# define WOLF_RENDER_H

# include "wolf/game.h"

typedef struct	s_wall
{
	int			top;
	int			bottom;
	float		size;
}				t_wall;

typedef struct	s_texture
{
	t_v2		pixel;
	int			tile;
	float		dist;
}				t_text;

extern void		game_render(t_game *game);

#endif
