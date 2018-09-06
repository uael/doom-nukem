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

#include "wolf/game.h"
#include "wolf/render.h"

int	game_init(t_game *g, t_world *world, t_me *me)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		return (-1);
	if (gpu_init(&g->gpu, 800, 800))
		return (-1);
	g->running = TRUE;
	g->world = world;
	g->me = me;
	return (0);
}

int	game_quit(t_game *game, const char *msg)
{
	const char *error;

	game->running = 0;
	gpu_destroy(&game->gpu);
	if (msg)
		ft_dprintf(2, "wolf3d: %s\n", msg);
	if (errno)
		ft_dprintf(2, "wolf3d: %m\n");
	if ((error = SDL_GetError()) && *error)
		ft_dprintf(2, "wolf3d: %s\n", error);
	SDL_Quit();
	exit(error && *error ? 1 : 0);
}

int	game_loop(t_game *game)
{
	SDL_Event	e;
	int			t0;
	int			t1;
	int			ms;

	game_render(game);
	while (game->running)
	{
		SDL_PollEvent(&e);
		t0 = SDL_GetTicks();
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE
			|| e.key.keysym.sym == SDLK_END)
			break ;
		if (game->me->velocity.x || game->me->velocity.y
			|| e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_a
			|| e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_d
			|| e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT)
			game_render(game);
		t1 = SDL_GetTicks();
		ms = 14 - (t1 - t0);
		SDL_Delay((uint32_t)(ms < 0 ? 0 : ms));
	}
	return (game_quit(game, NULL));
}
