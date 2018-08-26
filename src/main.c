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
#include <stdio.h>

typedef struct	s_world
{
	uint8_t		width;
	uint8_t		height;
	const char	**flooring;
	const char	**walling;
	const char	**ceiling;
}				t_world;

typedef struct	s_me
{
	t_line		fov;
	t_point		where;
	t_point		velocity;
	double		speed;
	double		accel;
	double		theta;
}				t_me;

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

typedef struct	s_game
{
	t_gpu			gpu;
	t_bool			running;
	const t_world	*world;
	t_me			*me;
	const uint8_t	*key;
}				t_game;

typedef struct	s_wall
{
	int			top;
	int			bottom;
	double		size;
}				t_wall;

int game_quit(t_game *game);

static void me_move(t_me *me, const char **const walling,
					const uint8_t *key)
{
	t_point	last;

	last = me->where;
	if (key[SDL_SCANCODE_LEFT])
		me->theta -= 0.1f;
	if (key[SDL_SCANCODE_RIGHT])
		me->theta += 0.1f;
	if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S] || key[SDL_SCANCODE_D]
		|| key[SDL_SCANCODE_A])
	{
		const t_point ref = { 1.0f, 0.0f };
		const t_point dir = point_turn(ref, me->theta);
		const t_point acc = point_mul(dir, me->accel);
		if (key[SDL_SCANCODE_W])
			me->velocity = point_add(me->velocity, acc);
		if (key[SDL_SCANCODE_S])
			me->velocity = point_sub(me->velocity, acc);
		if (key[SDL_SCANCODE_D])
			me->velocity = point_add(me->velocity, point_rag(acc));
		if (key[SDL_SCANCODE_A])
			me->velocity = point_sub(me->velocity, point_rag(acc));
	}
	else
		me->velocity = point_mul(me->velocity, 1.0f - me->accel / me->speed);
	if (point_mag(me->velocity) > me->speed)
		me->velocity = point_mul(point_unit(me->velocity), me->speed);
	me->where = point_add(me->where, me->velocity);
	if (point_tile(me->where, walling))
	{
		t_hit hit = point_cast(last, me->velocity, walling);

		if (math_isfl(hit.where.x))
		{
			me->velocity.x = 0.0;
			me->velocity.y *= 0.95;
		}
		if (math_isfl(hit.where.y))
		{
			me->velocity.y = 0.0;
			me->velocity.x *= 0.95;
		}
		me->where = point_add(last, me->velocity);
		if (point_tile(me->where, walling))
		{
			me->velocity = (t_point){ 0.0, 0.0 };
			me->where = last;
		}
	}
}

static void	gpu_lock(t_gpu *gpu)
{
	void	*screen;
	int		pitch;

	SDL_LockTexture(gpu->texture, NULL, &screen, &pitch);
	gpu->display.pixels = (uint32_t*) screen;
	gpu->display.width = pitch / (int) sizeof(uint32_t);
}

static void gpu_put(t_gpu *gpu, const int x, const int y,
					const uint32_t pixel)
{
	gpu->display.pixels[y + x * gpu->display.width] = pixel;
}

// Unlocks the gpu, making the pointer to video memory ready for presentation
static void gpu_unlock(t_gpu *gpu)
{
	SDL_UnlockTexture(gpu->texture);
}

static void wall_project(t_wall *wall, const int xres, const int yres,
	const double focal, const t_point corrected)
{
	const double normal = corrected.x < 1e-2f ? 1e-2f : corrected.x;
	const double size = 0.5f * focal * xres / normal;
	const int top = (const int) ((yres + size) / 2.0f);
	const int bot = (const int) ((yres - size) / 2.0f);

	wall->top = top > yres ? yres : top;
	wall->bottom = bot < 0 ? 0 : bot;
	wall->size = size;
}

// Presents the software gpu to the window.
// Calls the real GPU to rotate texture back 90 degrees before presenting.
static void gpu_present(const t_gpu *gpu)
{
	const SDL_Rect dst = {
		(gpu->width - gpu->height) / 2,
		(gpu->height - gpu->width) / 2,
		gpu->height, gpu->width,
	};
	SDL_RenderCopyEx(gpu->renderer, gpu->texture, NULL, &dst, -90, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(gpu->renderer);
}

static uint32_t color(const int tile)
{
	switch(tile)
	{
		default:
		case 1: return 0x00AA0000; // Red.
		case 2: return 0x0000AA00; // Green.
		case 3: return 0x000000AA; // Blue.
	}
}

int game_renderer(t_game *game)
{
	int x;
	int y;
	t_line camera;
	t_wall wall;

	game->key = SDL_GetKeyboardState(NULL);
	me_move(game->me, game->world->walling, game->key);
	camera = line_rotate(game->me->fov, game->me->theta);
	gpu_lock(&game->gpu);
	for(x = 0; x < game->gpu.width; x++)
	{
		const t_point dir = line_lerp(camera, x / (float) game->gpu.width);
		const t_hit hit = point_cast(game->me->where, dir, game->world->walling);
		const t_line trace = { game->me->where, hit.where };

		wall_project(&wall, game->gpu.width, game->gpu.height, game->me->fov.a.x, point_turn(point_sub(hit.where, game->me->where), -game->me->theta));
		for (y = 0; y < wall.bottom; y++)
			gpu_put(&game->gpu, x, y, color(point_tile(line_lerp(trace, -point_pcast(wall.size, game->gpu.height, y)), game->world->flooring)));
		for (y = wall.bottom; y < wall.top; y++)
			gpu_put(&game->gpu, x, y, color(hit.tile));
		for (y = wall.top; y < game->gpu.height; y++)
			gpu_put(&game->gpu, x, y, color(point_tile(line_lerp(trace, +point_pcast(wall.size, game->gpu.height, y)), game->world->ceiling)));
	}
	gpu_unlock(&game->gpu);
	gpu_present(&game->gpu);


	return 0;
}

int game_loop(t_game *game)
{
	SDL_Event	e;
	int			t0;
	int			t1;
	int			ms;

	game_renderer(game);
	while (game->running)
	{
		SDL_PollEvent(&e);
		t0 = SDL_GetTicks();
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE
			|| e.key.keysym.sym == SDLK_END)
			return (game_quit(game));
		if (game->me->velocity.x || game->me->velocity.y
			|| e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_a
			|| e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_d
			|| e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT)
			game_renderer(game);
		t1 = SDL_GetTicks();
		ms = 14 - (t1 - t0);
		SDL_Delay((uint32_t)(ms < 0 ? 0 : ms));
	}
	return (game_quit(game));
}

int gpu_init(t_gpu *gpu, int width, int height)
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

void	gpu_destroy(t_gpu *gpu)
{
	gpu->win ? SDL_DestroyWindow(gpu->win) : 0;
	gpu->renderer ? SDL_DestroyRenderer(gpu->renderer) : 0;
	gpu->texture ? SDL_DestroyTexture(gpu->texture) : 0;
}

int game_init(t_game *g, const t_world *world, t_me *me)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		return -1;
	if (gpu_init(&g->gpu, 1600, 1200))
		return -1;
	g->running = TRUE;
	g->world = world;
	g->me = me;
	return 0;
}

int game_quit(t_game *game)
{
	const char *error;

	game->running = 0;
	gpu_destroy(&game->gpu);
	if ((error = SDL_GetError()) && *error)
		ft_dprintf(2, "wolf3d: %s\n", error);
	SDL_Quit();
	exit(error && *error ? 1 : 0);
}

static const t_world world = {
	.width = 45,
	.height= 7,
	.ceiling = (const char*[]){
		"111111111111111111111111111111111111111111111",
		"122223223232232111111111111111222232232322321",
		"122222221111232111111111111111222222211112321",
		"122221221232323232323232323232222212212323231",
		"122222221111232111111111111111222222211112321",
		"122223223232232111111111111111222232232322321",
		"111111111111111111111111111111111111111111111",
	},
	.walling = (const char*[]){
		"111111111111111111111111111111111111111111111",
		"100000000000000111111111111111000000000000001",
		"103330001111000111111111111111033300011110001",
		"103000000000000000000000000000030000030000001",
		"103330001111000111111111111111033300011110001",
		"100000000000000111111111111111000000000000001",
		"111111111111111111111111111111111111111111111",
	},
	.flooring = (const char*[]){
		"111111111111111111111111111111111111111111111",
		"122223223232232111111111111111222232232322321",
		"122222221111232111111111111111222222211112321",
		"122222221232323323232323232323222222212323231",
		"122222221111232111111111111111222222211112321",
		"122223223232232111111111111111222232232322321",
		"111111111111111111111111111111111111111111111",
	},
};

static t_me me = {
	{ { 0.8, -1.0 }, { 0.8, +1.0 } },
	{ 7, 3.5 },
	{ 0.0, 0.0 },
	0.10,
	0.015,
	0.0
};

#undef main
int	main(int ac, char *av[])
{
	t_game game;

	(void)ac;
	(void)av;
	ft_bzero(&game, sizeof(t_game));
	if (game_init(&game, &world, &me))
		return (game_quit(&game));
	return (game_loop(&game));
}
