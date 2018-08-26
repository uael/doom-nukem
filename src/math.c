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

inline double	v2_slope(t_v2 a)
{
	return (a.y / a.x);
}

inline t_v2	v2_sh(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.x = b.x > 0.0f ? math_fl(a.x + 1.0f) : math_cl(a.x - 1.0f);
	c.y = v2_slope(b) * (c.x - a.x) + a.y;
	return (c);
}

inline t_v2	v2_sv(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.y = b.y > 0.0f ? math_fl(a.y + 1.0f) : math_cl(a.y - 1.0f);
	c.x = (c.y - a.y) / v2_slope(b) + a.x;
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

inline double	v2_pcast(double size, int yres, int y)
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
