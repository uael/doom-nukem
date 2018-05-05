/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL2/SDL.h>
# include <libft.h>

struct s_wl;

typedef struct		s_display
{
	uint32_t		*pixels;
	int				len;
}					t_display;

typedef struct		s_field
{

}					t_field;

typedef void		(t_eventcb)(struct s_wl *wl, SDL_Event *ev);

typedef struct		s_wl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				width;
	int				height;
	t_display		display;
	t_field			field;

	t_eventcb		*events[SDL_LASTEVENT];
}					t_wl;

extern void			wl_init(t_wl *wl, int x, int y);
extern int			wl_exit(t_wl *wl, int ecode, char const *msg, ...);
extern void			wl_listen(t_wl *wl, SDL_EventType type, t_eventcb *cb);
extern void			wl_put(t_wl *wl, int x, int y, uint32_t color);
extern void			wl_lock(t_wl *wl);
extern void			wl_draw(t_wl *wl);

#endif
