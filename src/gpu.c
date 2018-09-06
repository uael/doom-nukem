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
		return (-1);
	if (!(gpu->renderer = SDL_CreateRenderer(gpu->win, -1,
		SDL_RENDERER_PRESENTVSYNC)))
		return (-1);
	if (!(gpu->screen = SDL_CreateTexture(gpu->renderer,
		SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING,
		height - 200, width)))
		return (-1);
	gpu->width = width;
	gpu->height = height - 200;
	IMG_Init(IMG_INIT_PNG);
	if (!(gpu->walls = IMG_Load("asset/walls.png")))
		return (-1);
	SDL_LockSurface(gpu->walls);
	if (!(gpu->weapons = IMG_Load("asset/weapons.png")))
		return (-1);
	SDL_LockSurface(gpu->weapons);
	if (gpu->weapons->w != WEAPONS_W || gpu->weapons->h != WEAPONS_H)
		return (-1);
	return (0);
}

inline void	gpu_destroy(t_gpu *gpu)
{
	if (gpu->win)
		SDL_DestroyWindow(gpu->win);
	if (gpu->renderer)
		SDL_DestroyRenderer(gpu->renderer);
	if (gpu->screen)
		SDL_DestroyTexture(gpu->screen);
	if (gpu->walls)
	{
		SDL_UnlockSurface(gpu->walls);
		SDL_FreeSurface(gpu->walls);
	}
	if (gpu->weapons)
	{
		SDL_UnlockSurface(gpu->weapons);
		SDL_FreeSurface(gpu->weapons);
	}
}

inline void	gpu_lock(t_gpu *gpu)
{
	void	*screen;
	int		pitch;

	SDL_LockTexture(gpu->screen, NULL, &screen, &pitch);
	gpu->display.pixels = (uint32_t *)screen;
	gpu->display.width = pitch / (int)sizeof(uint32_t);
}

inline void	gpu_put(t_gpu *gpu, const int x, const int y,
					const uint32_t pixel)
{
	gpu->display.pixels[y + x * gpu->display.width] = pixel;
}

inline void	gpu_unlock(const t_gpu *gpu)
{
	SDL_UnlockTexture(gpu->screen);
	SDL_RenderCopyEx(gpu->renderer, gpu->screen, NULL,
		&(SDL_Rect){
			(gpu->width - gpu->height) / 2,
			(gpu->height - gpu->width) / 2,
			gpu->height, gpu->width,
		}, -90, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(gpu->renderer);
}
