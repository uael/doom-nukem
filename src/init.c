/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	wl_init(t_wl *wl, int x, int y)
{
	bzero(wl, sizeof(t_wl));
	SDL_Init(SDL_INIT_VIDEO);
	if (!(wl->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN)))
		wl_exit(wl, EXIT_FAILURE, "%s\n", SDL_GetError());
	if (!(wl->renderer = SDL_CreateRenderer(wl->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		wl_exit(wl, EXIT_FAILURE, "%s\n", SDL_GetError());
	if (!(wl->texture = SDL_CreateTexture(wl->renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, y, x)))
		wl_exit(wl, EXIT_FAILURE, "%s\n", SDL_GetError());
}

int		wl_exit(t_wl *wl, int ecode, char const *msg, ...)
{
	va_list ap;

	if (wl->texture)
		SDL_DestroyTexture(wl->texture);
	if (wl->renderer)
		SDL_DestroyRenderer(wl->renderer);
	if (wl->window)
		SDL_DestroyWindow(wl->window);
	if (msg)
	{
		if (isatty(STDERR_FILENO))
			ft_fprintf(g_stderr, CLR_RED"wolf3d: "CLR_RESET);
		else
			ft_fprintf(g_stderr, "wolf3d: ");
		va_start(ap, msg);
		ft_vfprintf(g_stderr, msg, ap);
		va_end(ap);
	}
	exit(ecode);
}

void	wl_listen(t_wl *wl, SDL_EventType type, t_eventcb *cb);
void	wl_put(t_wl *wl, int x, int y, uint32_t color);
void	wl_lock(t_wl *wl);
void	wl_draw(t_wl *wl);