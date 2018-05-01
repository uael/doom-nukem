/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftx/hit.h"

static int		tile(const t_v2 a, const char** const tiles)
{
	return tiles[(int)a.x][(int)a.y] - '0';
}

static float	dec(const float x)
{
	return (x - (int)x);
}

t_hit			ftx_hitcast(t_v2 where, t_v2 dir, char const **walling)
{
	const t_v2 hor = ftx_v2sh(where, dir);
	const t_v2 ver = ftx_v2sv(where, dir);
	const t_v2 ray = ftx_v2mag(ftx_v2sub(hor, where)) <
		ftx_v2mag(ftx_v2sub(ver, where)) ? hor : ver;
	const t_v2 dc = ftx_v2mul(dir, 0.01f);
	const t_v2 dx = { dc.x, 0.0f };
	const t_v2 dy = { 0.0f, dc.y };
	const t_v2 test = ftx_v2add(ray, ftx_v2mag(ftx_v2sub(hor, ver)) <
		1e-3f ? dc : dec(ray.x) == 0.0f ? dx : dy);
	const t_hit hit = { tile(test, walling), ray };

	return (hit.tile ? hit : ftx_hitcast(ray, dir, walling));
}
