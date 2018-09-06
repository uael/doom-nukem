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

#include <assert.h>
#include "wolf/render.h"

static uint32_t		get_super_color(t_gpu *gpu, int tile, t_v2 pixel)
{
	int x;
	int y;
	int tx;
	int ty;
	int ret;
	int ret2;

	x = (int)(fabsf((int)pixel.x - pixel.x) * WALLS_TEXTURE_SIZE);
	y = (int)(fabsf((int)pixel.y - pixel.y) * WALLS_TEXTURE_SIZE);

	tx = ((tile % WALLS_MX) * WALLS_TEXTURE_SIZE) + x;
	ty = ((tile / WALLS_MX) * WALLS_TEXTURE_SIZE) + y;

	ret2 = (gpu->walls->pitch / sizeof(uint32_t));
	ret = ((gpu->walls->pitch / sizeof(uint32_t)) * ty) + tx;

	return ((uint32_t *)gpu->walls->pixels)[ret];
}


static void			wall_project(t_wall *wall, t_v2 res, float focal, t_v2 corr)
{
	float	normal;
	float	size;
	int		top;
	int		bot;

	normal = corr.x < 1e-2f ? 1e-2f : corr.x;
	size = 0.5f * focal * (int)res.x / normal;
	top = (int)(((int)res.y + size) / 2.0f);
	bot = (int)(((int)res.y - size) / 2.0f);
	wall->top = top > (int)res.y ? (int)res.y : top;
	wall->bottom = bot < 0 ? 0 : bot;
	wall->size = size;
}

static uint32_t		get_color(const int tile)
{
	if (tile == 3)
		return (0x000000AA);
	if (tile == 2)
		return (0x0000AA00);
	return (0x00AA0000);
}

static void			render_column(t_game *game, int x, t_hit hit,
	const t_wall *wall)
{
	int			y;
	t_line		trace;
	t_v2		pixel;
	uint32_t	color;

	trace.a = game->me->where;
	trace.b = hit.where;
	y = 0;
	while (y < wall->bottom)
	{
		pixel = line_lerp(trace, -v2_pcast(wall->size, game->gpu.height, y));
		color = get_super_color(&game->gpu, world_tile(game->world, game->world->floor, pixel), pixel);
		gpu_put(&game->gpu, x, y, color);
		++y;
	}
	while (y < wall->top)
	{
		gpu_put(&game->gpu, x, y++, get_color(hit.tile));
	}
	while (y < game->gpu.height)
	{
		pixel = line_lerp(trace, v2_pcast(wall->size, game->gpu.height, y));
		color = get_super_color(&game->gpu, world_tile(game->world, game->world->floor, pixel), pixel);
		gpu_put(&game->gpu, x, y, color);
		++y;
	}
}

void				game_render(t_game *game)
{
	int		x;
	t_line	camera;
	t_v2	dir;
	t_wall	wall;
	t_hit	hit;

	game->key = SDL_GetKeyboardState(NULL);
	me_move(game->me, game->world, game->key);
	camera = line_rotate(game->me->fov, game->me->theta);
	gpu_lock(&game->gpu);
	x = -1;
	while (++x < game->gpu.width)
	{
		dir = line_lerp(camera, x / (float)game->gpu.width);
		hit = world_cast(game->world, game->me->where, dir);
		wall_project(&wall,
			(t_v2){ game->gpu.width, game->gpu.height },
			game->me->fov.a.x,
			v2_turn(v2_sub(hit.where, game->me->where), -game->me->theta));
		render_column(game, x, hit, &wall);
	}
	gpu_unlock(&game->gpu);
}