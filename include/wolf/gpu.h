/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf/gpu.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_GPU_H
# define WOLF_GPU_H

# include <SDL2/SDL.h>

typedef struct	s_display
{
	uint32_t	*pixels;
	int			width;
}				t_display;

typedef struct	s_gpu
{
	SDL_Window		*win;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	int				width;
	int				height;
	t_display		display;
}				t_gpu;

extern int		gpu_init(t_gpu *gpu, int width, int height);
extern void		gpu_destroy(t_gpu *gpu);
extern void		gpu_lock(t_gpu *gpu);
extern void		gpu_put(t_gpu *gpu, int x, int y, uint32_t pixel);
extern void		gpu_unlock(const t_gpu *gpu);

#endif
