/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

t_display	wl_lock(t_wl *wl)
{
	void* screen;
	int pitch;
	t_display display;

	SDL_LockTexture(wl->texture, NULL, &screen, &pitch);
	display = (t_display ){ (uint32_t*) screen, pitch / (int)sizeof(uint32_t) };
	return display;
}

inline void	wl_put(t_display display, int x, int y, uint32_t color)
{
	display.pixels[y + x * display.size] = color;
}

void		wl_render(t_wl *wl)
{
	const SDL_Rect dst = {
		(wl->width - wl->height) / 2,
		(wl->height - wl->width) / 2,
		wl->height, wl->width,};

	SDL_RenderCopyEx(wl->renderer, wl->texture, NULL, &dst, -90, NULL,
		SDL_FLIP_NONE);
	SDL_RenderPresent(wl->renderer);
}
