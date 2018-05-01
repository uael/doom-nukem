/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_H
# define LIBFTX_H

#include <libft.h>
#include <SDL.h>

struct s_ftx;

typedef int			(t_ftx_hook)(struct s_ftx *ftx, SDL_Event *event);

typedef struct		s_ftx
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	Uint32			*pixels;
	t_ftx_hook		*hooks[SDL_LASTEVENT];
}					t_ftx;

extern int			ftx_init(t_ftx *ftx, char const *name, int w, int h);
extern int			ftx_exit(t_ftx *ftx, int code, char const *msg, ...);
extern int			ftx_hook(t_ftx *ftx, SDL_EventType type, t_ftx_hook *hook);
extern int			ftx_loop(t_ftx *ftx);

#endif
