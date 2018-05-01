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

#include <libftx.h>

int	ftx_init(t_ftx *ftx, char const *name, int w, int h)
{
	ft_bzero(ftx, sizeof(t_ftx));
	SDL_Init(SDL_INIT_VIDEO);
	if (!(ftx->win = SDL_CreateWindow(name,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0)))
		return (ftx_exit(ftx, EXIT_FAILURE, "Unable to create win\n"));
	if (!(ftx->renderer = SDL_CreateRenderer(ftx->win, -1, 0)))
		return (ftx_exit(ftx, EXIT_FAILURE, "Unable to create renderer\n"));
	if (!(ftx->texture = SDL_CreateTexture(ftx->renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h)))
		return (ftx_exit(ftx, EXIT_FAILURE, "Unable to create texture\n"));
	if (!(ftx->pixels = malloc((w * h) * sizeof(Uint32))))
		return (ftx_exit(ftx, EXIT_FAILURE, "%m\n"));
	ft_memset(ftx->pixels, 255, (w * h) * sizeof(Uint32));
	return (YEP);
}
