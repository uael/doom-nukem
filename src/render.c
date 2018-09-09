/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/09/08 18:03:32 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "wolf/render.h"

static inline void	text(t_text *text, t_game *game, t_v2 pixel, uint8_t *tiles)
{
	text->tile = world_tile(game->world, tiles, pixel);
	text->pixel = pixel;
	text->dist = v2_dist(game->me->where, pixel);
}

static inline void	draw(t_game *game, int x, int y, t_text *t)
{
	int			tx;
	int			ty;
	uint32_t	color;
	float		pct;
	uint8_t		rgba[4];

	if (!(t->tile--) || t->dist >= RENDER_DST)
		color = 0;
	else
	{
		tx = (int)(fabsf((int)t->pixel.x - t->pixel.x) * WALLS_TEXTURE_SIZE);
		ty = (int)(fabsf((int)t->pixel.y - t->pixel.y) * WALLS_TEXTURE_SIZE);
		tx += (t->tile % WALLS_MX) * WALLS_TEXTURE_SIZE;
		ty += (t->tile / WALLS_MX) * WALLS_TEXTURE_SIZE;
		color = *(uint32_t *)((uint8_t *)game->gpu.walls->pixels +
			(((WALLS_W * ty) + tx) * game->gpu.walls->format->BytesPerPixel));
		SDL_GetRGB(color, game->gpu.walls->format, rgba, rgba + 1, rgba + 2);
		pct = ((RENDER_DST - t->dist) / RENDER_DST);
		color = SDL_MapRGB(game->gpu.walls->format,
			(uint8_t)(rgba[0] * pct), (uint8_t)(rgba[1] * pct),
			(uint8_t)(rgba[2] * pct));
	}
	gpu_put(&game->gpu, x, y, color);
}

static inline void	render_y(t_game *game, int x, t_hit hit, const t_wall *wall)
{
	int			cen;
	int			y;
	t_line		tra;
	t_text		t;

	tra = (t_line){ game->me->where, hit.where };
	cen = game->gpu.h / 2;
	y = 0;
	while (y < game->gpu.h)
	{
		if (y < wall->bottom)
			text(&t, game, ln_lerp(tra, -v2_pcast(wall->size, game->gpu.h, y)),
				game->world->floor);
		else if (y > wall->top)
			text(&t, game, ln_lerp(tra, v2_pcast(wall->size, game->gpu.h, y)),
				game->world->ceil);
		else
		{
			t.pixel.x = hit.hor ? hit.where.y : hit.where.x;
			t.pixel.y = 0.5f - ((float)y - cen) / wall->size;
			t.tile = hit.tile;
			t.dist = v2_dist(game->me->where, hit.where);
		}
		draw(game, x, y++, &t);
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
	while (++x < game->gpu.w)
	{
		dir = ln_lerp(camera, x / (float)game->gpu.w);
		hit.from = game->me->where;
		world_cast(&hit, game->world, game->me->where, dir);
		wall_project(&wall, (t_v2){ game->gpu.w, game->gpu.h },
			game->me->fov.a.x,
			v2_turn(v2_sub(hit.where, game->me->where), -game->me->theta));
		render_y(game, x, hit, &wall);
	}
	gpu_unlock(&game->gpu);
}
