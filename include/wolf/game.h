/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf/game.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_GAME_H
# define WOLF_GAME_H

# include "wolf/gpu.h"
# include "wolf/me.h"

typedef struct	s_game
{
	t_gpu		gpu;
	t_bool		running;
	t_world		*world;
	t_me		*me;
}				t_game;

extern int		game_init(t_game *game, t_world *world, t_me *me);
extern int		game_quit(t_game *game, const char *msg);
extern int		game_loop(t_game *game);

#endif
