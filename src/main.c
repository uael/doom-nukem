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
#include <pthread.h>
#include <semaphore.h>

typedef struct	s_game
{
	t_bool		running;
	sem_t		calculate;
	pthread_t	calculator;
	sem_t		render;
	pthread_t	renderer;
	SDL_Window	*win;
}				t_game;

static int wl_quit(void)
{
	const char *error;

	if ((error = SDL_GetError()) && *error)
		ft_fprintf(g_stderr, "wolf3d: %s\n", error);
	SDL_Quit();
	return error && *error ? 1 : 0;
}

void *calculator(t_game *game)
{
	while (game->running) {
		sem_wait(&game->calculate);
		puts("calculate !");
	}
	return NULL;
}


void *renderer(t_game *game)
{
	while (game->running) {
		sem_wait(&game->render);
		puts("render !");
	}
	return NULL;
}

typedef void (t_keydown)(t_game *game, SDL_Event *event);

void on_escape(t_game *game, SDL_Event *event)
{
	(void)game;
	(void)event;
	wl_quit();
}

void on_r(t_game *game, SDL_Event *event)
{
	(void)event;
	sem_post(&game->render);
}

void on_c(t_game *game, SDL_Event *event)
{
	(void)event;
	sem_post(&game->calculate);
}

static t_keydown *g_keydown[UINT8_MAX] = {
	[SDLK_ESCAPE] = on_escape,
	[SDLK_c] = on_c,
	[SDLK_r] = on_r,
};

int game_loop(t_game *game)
{
	SDL_Event event;

	while (game->running && SDL_WaitEvent(&event)) {
		printf("Event: %d\n", event.key.keysym.sym);
		switch (event.type) {
			case SDL_QUIT:
				return wl_quit();
			case SDL_KEYDOWN:
				if (event.key.keysym.sym < UINT8_MAX
					&& g_keydown[event.key.keysym.sym])
					g_keydown[event.key.keysym.sym](game, &event);
				break;
			default:
				break;
		}
	}
	return wl_quit();
}

int	main(int ac, char *av[])
{
	t_game game;

	(void)ac;
	(void)av;
	if (SDL_Init(SDL_INIT_VIDEO))
		return wl_quit();
	game.running = TRUE;
	if (sem_init(&game.calculate, 0, 0))
		return wl_quit();
	if (pthread_create(&game.calculator, NULL, (void *)calculator, &game))
		return wl_quit();
	if (sem_init(&game.render, 0, 0))
		return wl_quit();
	if (pthread_create(&game.renderer, NULL, (void *)renderer, &game))
		return wl_quit();
	if (!(game.win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)))
		return wl_quit();
	return (game_loop(&game));
}
