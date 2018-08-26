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

inline t_point	point_turn(const t_point a, const double t)
{
	t_point b;

	b.x = a.x * cos(t) - a.y * sin(t);
	b.y = a.x * sin(t) + a.y * cos(t);
	return (b);
}

inline t_point	point_rag(const t_point a)
{
	t_point b;

	b.x = -a.y;
	b.y = a.x;
	return (b);
}

inline t_point	point_sub(const t_point a, const t_point b)
{
	t_point c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

inline t_point	point_add(const t_point a, const t_point b)
{
	t_point c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

inline t_point	point_mul(const t_point a, const double n)
{
	t_point b;

	b.x = a.x * n;
	b.y = a.y * n;
	return (b);
}

inline double	point_mag(const t_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

inline t_point	point_unit(const t_point a)
{
	return (point_mul(a, 1.0 / point_mag(a)));
}

inline double	point_slope(const t_point a)
{
	return (a.y / a.x);
}

inline t_point	point_sh(const t_point a, const t_point b)
{
	t_point c;

	c.x = b.x > 0.0f ? math_fl(a.x + 1.0f) : math_cl(a.x - 1.0f);
	c.y = point_slope(b) * (c.x - a.x) + a.y;
	return (c);
}

inline t_point	point_sv(const t_point a, const t_point b)
{
	t_point c;

	c.y = b.y > 0.0f ? math_fl(a.y + 1.0f) : math_cl(a.y - 1.0f);
	c.x = (c.y - a.y) / point_slope(b) + a.x;
	return (c);
}

inline int		point_tile(const t_point a, const char **const tiles)
{
	return (tiles[(int)a.y][(int)a.x] - '0');
}

inline double	math_dec(const double x)
{
	return (x - (int)x);
}

inline t_hit	point_cast(const t_point where, const t_point direction, const char **const walling)
{
	t_point hor = point_sh(where, direction);
	t_point ver = point_sv(where, direction);
	t_point ray = point_mag(point_sub(hor, where)) < point_mag(point_sub(ver, where)) ? hor : ver;
	t_point dc = point_mul(direction, 0.01f);
	t_point dx = { dc.x, 0.0f };
	t_point dy = { 0.0f, dc.y };
	t_point test = point_add(ray, point_mag(point_sub(hor, ver)) < 1e-3f ? dc :
		math_dec(ray.x) == 0.0f ? dx : dy);
	const t_hit hit = { point_tile(test, walling), ray };
	return (hit.tile ? hit : point_cast(ray, direction, walling));
}

inline double	point_pcast(const double size, const int yres, const int y)
{
	return (size / (2 * (y + 1) - yres));
}

inline t_line	line_rotate(const t_line l, const double t)
{
	t_line line;

	line.a = point_turn(l.a, t);
	line.b = point_turn(l.b, t);
	return (line);
}

inline t_point	line_lerp(const t_line l, const double n)
{
	return point_add(l.a, point_mul(point_sub(l.b, l.a), n));
}
