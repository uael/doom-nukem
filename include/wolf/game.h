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

# include <SDL2/SDL.h>

# include "field.h"

typedef struct		s_wl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				width;
	int				height;
	t_field			field;
}					t_wl;

extern void			wl_init(t_wl *wl, int x, int y);
extern int			wl_exit(t_wl *wl, int ecode, char const *msg, ...);
extern int			wl_isdone(t_wl *wl);
extern void			wl_handle(t_wl *wl, uint8_t const *keyboard);

#endif
