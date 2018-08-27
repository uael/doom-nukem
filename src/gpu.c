/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf/gpu.h"

inline int	gpu_init(t_gpu *gpu, int width, int height)
{
	if (!(gpu->win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN)))
		return -1;
	if (!(gpu->renderer = SDL_CreateRenderer(gpu->win, -1,
		SDL_RENDERER_ACCELERATED)))
		return -1;
	if (!(gpu->texture = SDL_CreateTexture(gpu->renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, height, width)))
		return -1;
	gpu->width = width;
	gpu->height = height;
	return 0;
}

inline void	gpu_destroy(t_gpu *gpu)
{
	gpu->win ? SDL_DestroyWindow(gpu->win) : 0;
	gpu->renderer ? SDL_DestroyRenderer(gpu->renderer) : 0;
	gpu->texture ? SDL_DestroyTexture(gpu->texture) : 0;
}

inline void	gpu_lock(t_gpu *gpu)
{
	void	*screen;
	int		pitch;

	SDL_LockTexture(gpu->texture, NULL, &screen, &pitch);
	gpu->display.pixels = (uint32_t *)screen;
	gpu->display.width = pitch / (int)sizeof(uint32_t);
}

inline void gpu_put(t_gpu *gpu, const int x, const int y,
					const uint32_t pixel)
{
	gpu->display.pixels[y + x * gpu->display.width] = pixel;
}

inline void gpu_unlock(const t_gpu *gpu)
{
	SDL_UnlockTexture(gpu->texture);
	SDL_RenderCopyEx(gpu->renderer, gpu->texture, NULL,
		&(SDL_Rect){
			(gpu->width - gpu->height) / 2,
			(gpu->height - gpu->width) / 2,
			gpu->height, gpu->width,
		}, -90, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(gpu->renderer);
}
