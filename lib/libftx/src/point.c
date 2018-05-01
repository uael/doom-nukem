/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libftx/point.h"
#include "libftx/math.h"

inline t_v2		ftx_v2turn(t_v2 a, float t)
{
	return ((t_v2){
		a.x * cosf(t) - a.y * sinf(t),
		a.x * sinf(t) + a.y * cosf(t) });
}

inline t_v2		ftx_v2rag(t_v2 a)
{
	return ((t_v2){ -a.y, a.x });
}

inline t_v2		ftx_v2sub(t_v2 a, t_v2 b)
{
	return ((t_v2){ a.x - b.x, a.y - b.y });
}

inline t_v2		ftx_v2add(t_v2 a, t_v2 b)
{
	return ((t_v2){ a.x + b.x, a.y + b.y });
}

inline t_v2		ftx_v2mul(t_v2 a, float n)
{
	return ((t_v2){ a.x * n, a.y * n });
}

inline float	ftx_v2mag(t_v2 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y));
}

inline t_v2		ftx_v2unit(t_v2 a)
{
	return (ftx_v2mul(a, 1.0f / ftx_v2mag(a)));
}

inline float	ftx_v2slope(t_v2 a)
{
	return (a.y / a.x);
}

inline t_v2		ftx_v2sh(t_v2 a, t_v2 b)
{
	const float x = b.x > 0.0f ? ftx_floor(a.x + 1.0f) : ftx_ceil(a.x - 1.0f);
	const float y = ftx_v2slope(b) * (x - a.x) + a.y;

	return ((t_v2){ x, y });
}

inline t_v2		ftx_v2sv(t_v2 a, t_v2 b)
{
	const float y = b.y > 0.0f ? ftx_floor(a.y + 1.0f) : ftx_ceil(a.y - 1.0f);
	const float x = (y - a.y) / ftx_v2slope(b) + a.x;

	return ((t_v2){ x, y });
}
