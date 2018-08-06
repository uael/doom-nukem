/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>
#include <libft.h>

typedef struct	s_game
{
	t_bool		running;
	SDL_sem		*calculate;
	SDL_Thread	*calculator;
	SDL_sem		*render;
	SDL_Thread	*renderer;
	SDL_Window	*win;
}				t_game;

int game_quit(t_game *game)
{
	const char *error;

	game->running = 0;
	game->calculate ? SDL_SemPost(game->calculate) : 0;
	game->render ? SDL_SemPost(game->render) : 0;
	game->calculator ? SDL_WaitThread(game->calculator, NULL) : 0;
	game->renderer ? SDL_WaitThread(game->renderer, NULL) : 0;
	game->calculate ? SDL_DestroySemaphore(game->calculate) : 0;
	game->render ? SDL_DestroySemaphore(game->render) : 0;
	game->win ? SDL_DestroyWindow(game->win) : 0;
	if ((error = SDL_GetError()) && *error)
		ft_dprintf(2, "wolf3d: %s\n", error);
	SDL_Quit();
	exit(error && *error ? 1 : 0);
}

void game_render(t_game *game)
{
	SDL_SemPost(game->render);
}

void game_calculate(t_game *game)
{
	SDL_SemPost(game->calculate);
}

int game_calculator(t_game *game)
{
	while (1)
	{
		SDL_SemWait(game->calculate);
		if (!game->running)
			break;
		ft_dprintf(2, "======> calculate !\n");
		game_render(game);
	}
	return 0;
}


int game_renderer(t_game *game)
{
	while (1)
	{
		SDL_SemWait(game->render);
		if (!game->running)
			break;
		ft_dprintf(2, "======> render !\n");
	}
	return 0;
}

typedef void (t_handler)(t_game *game, SDL_Event *event);

void on_escape(t_game *game, SDL_Event *event)
{
	(void)game;
	(void)event;
	game_quit(game);
}

void on_r(t_game *game, SDL_Event *event)
{
	(void)event;
	game_render(game);
}

void on_c(t_game *game, SDL_Event *event)
{
	(void)event;
	game_calculate(game);
}

static t_handler *g_keydown[UINT8_MAX] = {
	[SDLK_ESCAPE] = on_escape,
	[SDLK_c] = on_c,
	[SDLK_r] = on_r,
};

static t_handler *g_keyup[UINT8_MAX];

int game_loop(t_game *game)
{
	SDL_Event ev;

	while (game->running && SDL_WaitEvent(&ev))
		if (ev.type == SDL_QUIT)
			return game_quit(game);
		else if (ev.key.keysym.sym >= UINT8_MAX)
			continue ;
		else if (ev.type == SDL_KEYDOWN && g_keydown[ev.key.keysym.sym])
			g_keydown[ev.key.keysym.sym](game, &ev);
		else if (ev.type == SDL_KEYUP && g_keyup[ev.key.keysym.sym])
			g_keyup[ev.key.keysym.sym](game, &ev);
	return game_quit(game);
}

#undef main
int	main(int ac, char *av[])
{
	t_game game;

	(void)ac;
	(void)av;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		return game_quit(&game);
	game.running = TRUE;
	if (!(game.calculate = SDL_CreateSemaphore(0)))
		return game_quit(&game);
	if (!(game.renderer = SDL_CreateThread((void *)game_calculator, "01",
		&game)))
		return game_quit(&game);
	if (!(game.render = SDL_CreateSemaphore(0)))
		return game_quit(&game);
	if (!(game.renderer = SDL_CreateThread((void *)game_renderer, "02", &game)))
		return game_quit(&game);
	if (!(game.win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN)))
		return game_quit(&game);
	return (game_loop(&game));
}
