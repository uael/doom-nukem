/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/05/05 14:47:52 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <libftx.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
	int tile;
	t_v2 where;
} t_hit;

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int xres;
	int yres;
}
	Gpu;

typedef struct
{
	uint32_t* pixels;
	int width;
}
	Display;

typedef struct
{
	int top;
	int bot;
	float size;
}
	Wall;

typedef struct
{
	t_ln fov;
	t_v2 where;
	t_v2 velocity;
	float speed;
	float acceleration;
	float theta;
}
	Hero;

typedef struct
{
	const char** ceiling;
	const char** walling;
	const char** floring;
}
	Map;

// Returns a decimal value of the ascii tile value on the map.
static int tile(const t_v2 a, const char** const tiles)
{
	const int x = a.x;
	const int y = a.y;
	return tiles[y][x] - '0';
}

// Floating point decimal.
static float dec(const float x)
{
	return x - (int) x;
}

// Casts a ray from <where> in unit <direction> until a <walling> tile is hit.
static t_hit cast(const t_v2 where, const t_v2 direction, const char** const walling)
{
	// Determine whether to step horizontally or vertically on the grid.
	const t_v2 hor = ftx_v2sh(where, direction);
	const t_v2 ver = ftx_v2sv(where, direction);
	const t_v2 ray = ftx_v2mag(ftx_v2sub(hor, where)) < ftx_v2mag(ftx_v2sub(ver, where)) ? hor : ver;
	// Due to floating point error, the step may not make it to the next grid square.
	// Three directions (dy, dx, dc) of a tiny step will be added to the ray
	// depending on if the ray hit a horizontal wall, a vertical wall, or the corner
	// of two walls, respectively.
	const t_v2 dc = ftx_v2mul(direction, 0.01f);
	const t_v2 dx = { dc.x, 0.0f };
	const t_v2 dy = { 0.0f, dc.y };
	const t_v2 test = ftx_v2add(ray,
		// Tiny step for corner of two grid squares.
		ftx_v2mag(ftx_v2sub(hor, ver)) < 1e-3f ? dc :
			// Tiny step for vertical grid square.
			dec(ray.x) == 0.0f ? dx :
				// Tiny step for a horizontal grid square.
				dy);
	const t_hit hit = { tile(test, walling), ray };
	// If a wall was not hit, then continue advancing the ray.
	return hit.tile ? hit : cast(ray, direction, walling);
}

// Party casting. Returns a percentage of <y> related to <yres> for ceiling and
// floor casting when lerping the floor or ceiling.
static float pcast(const float size, const int yres, const int y)
{
	return size / (2 * (y + 1) - yres);
}

// Presents the software gpu to the window.
// Calls the real GPU to rotate texture back 90 degrees before presenting.
static void present(const Gpu gpu)
{
	const SDL_Rect dst = {
		(gpu.xres - gpu.yres) / 2,
		(gpu.yres - gpu.xres) / 2,
		gpu.yres, gpu.xres,
	};
	SDL_RenderCopyEx(gpu.renderer, gpu.texture, NULL, &dst, -90, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(gpu.renderer);
}

// Locks the gpu, returning a pointer to video memory.
static Display lock(const Gpu gpu)
{
	void* screen;
	int pitch;
	SDL_LockTexture(gpu.texture, NULL, &screen, &pitch);
	const Display display = { (uint32_t*) screen, pitch / (int) sizeof(uint32_t) };
	return display;
}

// Places a pixels in gpu video memory.
static void put(const Display display, const int x, const int y, const uint32_t pixel)
{
	display.pixels[y + x * display.width] = pixel;
}

// Unlocks the gpu, making the pointer to video memory ready for presentation
static void unlock(const Gpu gpu)
{
	SDL_UnlockTexture(gpu.texture);
}

// Spins the hero when keys h,l are held down.
static Hero spin(Hero hero, const uint8_t* key)
{
	if(key[SDL_SCANCODE_H]) hero.theta -= 0.1f;
	if(key[SDL_SCANCODE_L]) hero.theta += 0.1f;
	return hero;
}

// Moves the hero when w,a,s,d are held down. Handles collision detection for the walls.
static Hero move(Hero hero, const char** const walling, const uint8_t* key)
{
	const t_v2 last = hero.where, zero = { 0.0f, 0.0f };
	// Accelerates with key held down.
	if(key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S] || key[SDL_SCANCODE_D] || key[SDL_SCANCODE_A])
	{
		const t_v2 reference = { 1.0f, 0.0f };
		const t_v2 direction = ftx_v2turn(reference, hero.theta);
		const t_v2 acceleration = ftx_v2mul(direction, hero.acceleration);
		if(key[SDL_SCANCODE_W]) hero.velocity = ftx_v2add(hero.velocity, acceleration);
		if(key[SDL_SCANCODE_S]) hero.velocity = ftx_v2sub(hero.velocity, acceleration);
		if(key[SDL_SCANCODE_D]) hero.velocity = ftx_v2add(hero.velocity, ftx_v2rag(acceleration));
		if(key[SDL_SCANCODE_A]) hero.velocity = ftx_v2sub(hero.velocity, ftx_v2rag(acceleration));
	}
		// Otherwise, decelerates (exponential decay).
	else hero.velocity = ftx_v2mul(hero.velocity, 1.0f - hero.acceleration / hero.speed);
	// Caps velocity if top speed is exceeded.
	if(ftx_v2mag(hero.velocity) > hero.speed) hero.velocity = ftx_v2mul(ftx_v2unit(hero.velocity), hero.speed);
	// Moves.
	hero.where = ftx_v2add(hero.where, hero.velocity);
	// Sets velocity to zero if there is a collision and puts hero back in bounds.
	if(tile(hero.where, walling))
	{
		hero.velocity = zero;
		hero.where = last;
	}
	return hero;
}

// Returns a color value (RGB) from a decimal tile value.
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

// Calculations wall size using the <corrected> ray to the wall.
static Wall project(const int xres, const int yres, const float focal, const t_v2 corrected)
{
	// Normal distance of corrected ray is clamped to some small value else wall size will shoot to infinity.
	const float normal = corrected.x < 1e-2f ? 1e-2f : corrected.x;
	const float size = 0.5f * focal * xres / normal;
	const int top = (yres + size) / 2.0f;
	const int bot = (yres - size) / 2.0f;
	// Top and bottom values are clamped to screen size else renderer will waste cycles
	// (or segfault) when rasterizing pixels off screen.
	const Wall wall = { top > yres ? yres : top, bot < 0 ? 0 : bot, size };
	return wall;
}

// Renders the entire scene from the <hero> perspective given a <map> and a software <gpu>.
static void render(const Hero hero, const Map map, const Gpu gpu)
{
	const int t0 = SDL_GetTicks();
	const t_ln camera = ftx_lnrot(hero.fov, hero.theta);
	const Display display = lock(gpu);
	// Ray cast for all columns of the window.
	for(int x = 0; x < gpu.xres; x++)
	{
		const t_v2 direction = ftx_lnlerp(camera, x / (float) gpu.xres);
		const t_hit hit = cast(hero.where, direction, map.walling);
		const t_v2 ray = ftx_v2sub(hit.where, hero.where);
		const t_ln trace = { hero.where, hit.where };
		const t_v2 corrected = ftx_v2turn(ray, -hero.theta);
		const Wall wall = project(gpu.xres, gpu.yres, hero.fov.a.x, corrected);
		// Renders flooring.
		for(int y = 0; y < wall.bot; y++)
			put(display, x, y, color(tile(ftx_lnlerp(trace, -pcast(wall.size, gpu.yres, y)), map.floring)));
		// Renders wall.
		for(int y = wall.bot; y < wall.top; y++)
			put(display, x, y, color(hit.tile));
		// Renders ceiling.
		for(int y = wall.top; y < gpu.yres; y++)
			put(display, x, y, color(tile(ftx_lnlerp(trace, +pcast(wall.size, gpu.yres, y)), map.ceiling)));
	}
	unlock(gpu);
	present(gpu);
	// Caps frame rate to ~60 fps if the vertical sync (VSYNC) init failed.
	const int t1 = SDL_GetTicks();
	const int ms = 16 - (t1 - t0);
	SDL_Delay(ms < 0 ? 0 : ms);
}

static bool done()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	return event.type == SDL_QUIT
		|| event.key.keysym.sym == SDLK_END
		|| event.key.keysym.sym == SDLK_ESCAPE;
}

static Hero born(const float focal)
{
	const Hero hero = {
		ftx_lnviewport(focal),
		// Where.
		{ 3.5f, 3.5f },
		// Velocity.
		{ 0.0f, 0.0f },
		// Speed.
		0.10f,
		// Acceleration.
		0.015f,
		// Theta radians.
		0.0f
	};
	return hero;
}

int main(int argc, char* argv[])
{
	Hero hero = born(0.8f);
	while(!done())
	{
		const uint8_t* key = SDL_GetKeyboardState(NULL);
		hero = spin(hero, key);
		hero = move(hero, map.walling, key);
		render(hero, map, gpu);
	}
	// No need to free anything - gives quick exit.
	return 0;
}
