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

static inline void	draw(t_game *game, int x, int y, t_v2 texture)
{
	int			tx;
	int			ty;
	int			i;
	int			tile;
	uint32_t	color;

	tile = world_tile(game->world, game->world->floor, texture);
	tx = (int)(fabsf((int)texture.x - texture.x) * WALLS_TEXTURE_SIZE);
	ty = (int)(fabsf((int)texture.y - texture.y) * WALLS_TEXTURE_SIZE);
	tx += (tile % WALLS_MX) * WALLS_TEXTURE_SIZE;
	ty += (tile / WALLS_MX) * WALLS_TEXTURE_SIZE;
	i = (WALLS_W * ty) + tx;
	color = *(uint32_t *)((uint8_t *)game->gpu.walls->pixels +
		(i * game->gpu.walls->format->BytesPerPixel));
	gpu_put(&game->gpu, x, y, color);
}

static inline void	rend_do(t_game *game, int x, t_hit hit, const t_wall *wall)
{
	int			begin;
	int			y;
	t_line		trace;
	t_v2		txt;

	trace.a = game->me->where;
	trace.b = hit.where;
	begin = game->gpu.height / 2;
	y = begin;
	while (y >= 0)
	{
		if (y >= wall->bottom)
		{
			txt = (t_v2){hit.hor ? hit.where.y : hit.where.x,
				0.5f - (((float)y - begin) / wall->size)};
		}
		else
			txt = line_lerp(trace, -v2_pcast(wall->size, game->gpu.height, y));
		draw(game, x, --y, txt);
	}
}

static inline void	rend_up(t_game *game, int x, t_hit hit, const t_wall *wall)
{
	int			begin;
	int			y;
	t_line		trace;
	t_v2		txt;

	trace.a = game->me->where;
	trace.b = hit.where;
	begin = game->gpu.height / 2;
	y = begin;
	while (y < game->gpu.height)
	{
		if (y < wall->top)
		{
			txt = (t_v2){hit.hor ? hit.where.y : hit.where.x,
				0.5f + (((float)y - begin) / wall->size)};
		}
		else
			txt = line_lerp(trace, v2_pcast(wall->size, game->gpu.height, y));
		draw(game, x, y++, txt);
	}
}

static inline void	wall_project(t_wall *wall, t_v2 res, float focal, t_v2 corr)
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

void				game_render(t_game *game)
{
	int		x;
	t_line	camera;
	t_v2	dir;
	t_wall	wall;
	t_hit	hit;

	me_move(game->me, game->world, SDL_GetKeyboardState(NULL));
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
		rend_do(game, x, hit, &wall);
		rend_up(game, x, hit, &wall);
	}
	gpu_unlock(&game->gpu);
}
