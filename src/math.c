/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>
#include <libft.h>

inline int		math_fl(const double x)
{
	return ((int)x - (x < (int)x));
}

inline int		math_cl(const double x)
{
	return ((int)x + (x > (int)x));
}

inline int		math_isfl(double x)
{
	return (fabs((int)x - x) < 0.01);
}

inline t_v2	v2_turn(t_v2 a, double t)
{
	t_v2 b;

	b.x = a.x * cos(t) - a.y * sin(t);
	b.y = a.x * sin(t) + a.y * cos(t);
	return (b);
}

inline t_v2	v2_rag(t_v2 a)
{
	t_v2 b;

	b.x = -a.y;
	b.y = a.x;
	return (b);
}

inline t_v2	v2_sub(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

inline t_v2	v2_add(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

inline t_v2	v2_mul(t_v2 a, double n)
{
	t_v2 b;

	b.x = a.x * n;
	b.y = a.y * n;
	return (b);
}

inline double	v2_mag(t_v2 a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

inline t_v2	v2_unit(t_v2 a)
{
	return (v2_mul(a, 1.0 / v2_mag(a)));
}

inline double	point_slope(const t_v2 a)
{
	return (a.y / a.x);
}

inline t_v2	point_sh(const t_v2 a, const t_v2 b)
{
	t_v2 c;

	c.x = b.x > 0.0f ? math_fl(a.x + 1.0f) : math_cl(a.x - 1.0f);
	c.y = point_slope(b) * (c.x - a.x) + a.y;
	return (c);
}

inline t_v2	point_sv(const t_v2 a, const t_v2 b)
{
	t_v2 c;

	c.y = b.y > 0.0f ? math_fl(a.y + 1.0f) : math_cl(a.y - 1.0f);
	c.x = (c.y - a.y) / point_slope(b) + a.x;
	return (c);
}

inline int		v2_tile(t_v2 a, const char **tiles)
{
	return (tiles[(int)a.y][(int)a.x] - '0');
}

inline double	math_dec(const double x)
{
	return (x - (int)x);
}

inline t_hit	v2_cast(t_v2 where, t_v2 direction, const char **walling)
{
	t_v2 hor = point_sh(where, direction);
	t_v2 ver = point_sv(where, direction);
	t_v2 ray = v2_mag(v2_sub(hor, where)) < v2_mag(v2_sub(ver, where)) ? hor : ver;
	t_v2 dc = v2_mul(direction, 0.01f);
	t_v2 dx = { dc.x, 0.0f };
	t_v2 dy = { 0.0f, dc.y };
	t_v2 test = v2_add(ray, v2_mag(v2_sub(hor, ver)) < 1e-3f ? dc :
							math_dec(ray.x) == 0.0f ? dx : dy);
	const t_hit hit = {v2_tile(test, walling), ray };
	return (hit.tile ? hit : v2_cast(ray, direction, walling));
}

inline double	point_pcast(const double size, const int yres, const int y)
{
	return (size / (2 * (y + 1) - yres));
}

inline t_line	line_rotate(const t_line l, const double t)
{
	t_line line;

	line.a = v2_turn(l.a, t);
	line.b = v2_turn(l.b, t);
	return (line);
}

inline t_v2	line_lerp(const t_line l, const double n)
{
	return v2_add(l.a, v2_mul(v2_sub(l.b, l.a), n));
}
