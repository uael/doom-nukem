/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf/render.h"

static void		wall_project(t_wall *wall, const int xres, const int yres,
						 const float focal, const t_v2 corrected)
{
	const float normal = corrected.x < 1e-2f ? 1e-2f : corrected.x;
	const float size = 0.5f * focal * xres / normal;
	const int top = (const int) ((yres + size) / 2.0f);
	const int bot = (const int) ((yres - size) / 2.0f);

	wall->top = top > yres ? yres : top;
	wall->bottom = bot < 0 ? 0 : bot;
	wall->size = size;
}

static uint32_t	color(const int tile)
{
	switch(tile)
	{
		default:
		case 1: return 0x00AA0000; // Red.
		case 2: return 0x0000AA00; // Green.
		case 3: return 0x000000AA; // Blue.
	}
}

void			game_render(t_game *game)
{
	int		x;
	int		y;
	t_line	camera;
	t_wall	wall;

	game->key = SDL_GetKeyboardState(NULL);
	me_move(game->me, game->world, game->key);
	camera = line_rotate(game->me->fov, game->me->theta);
	gpu_lock(&game->gpu);
	for (x = 0; x < game->gpu.width; x++)
	{
		const t_v2 dir = line_lerp(camera, x / (float) game->gpu.width);
		const t_hit hit = world_cast(game->world, game->me->where, dir);
		const t_line trace = { game->me->where, hit.where };

		wall_project(&wall, game->gpu.width, game->gpu.height, game->me->fov.a.x,
			v2_turn(v2_sub(hit.where, game->me->where),
				-game->me->theta));
		for (y = 0; y < wall.bottom; y++)
			gpu_put(&game->gpu, x, y, color(world_tile(
				game->world, game->world->floor,
				line_lerp(trace, -v2_pcast(wall.size, game->gpu.height, y)))));
		for (y = wall.bottom; y < wall.top; y++)
			gpu_put(&game->gpu, x, y, color(hit.tile));
		for (y = wall.top; y < game->gpu.height; y++)
			gpu_put(&game->gpu, x, y, color(world_tile(
				game->world, game->world->ceil,
				line_lerp(trace, +v2_pcast(wall.size, game->gpu.height, y)))));
	}
	gpu_unlock(&game->gpu);
}
