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

inline int		math_fl(const float x)
{
	return ((int)x - (x < (int)x));
}

inline int		math_cl(const float x)
{
	return ((int)x + (x > (int)x));
}

inline int		math_isfl(float x)
{
	return (fabsf((int)x - x) < 0.000001f);
}

inline t_v2		v2_turn(t_v2 a, float t)
{
	t_v2 b;

	b.x = a.x * cosf(t) - a.y * sinf(t);
	b.y = a.x * sinf(t) + a.y * cosf(t);
	return (b);
}

inline t_v2		v2_rag(t_v2 a)
{
	t_v2 b;

	b.x = -a.y;
	b.y = a.x;
	return (b);
}

inline t_v2		v2_sub(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

inline t_v2		v2_add(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

inline t_v2		v2_mul(t_v2 a, float n)
{
	t_v2 b;

	b.x = a.x * n;
	b.y = a.y * n;
	return (b);
}

inline float	v2_mag(t_v2 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y));
}

inline t_v2		v2_unit(t_v2 a)
{
	return (v2_mul(a, 1.0f / v2_mag(a)));
}

inline float	v2_slope(t_v2 a)
{
	return (a.y / a.x);
}

inline t_v2		v2_steps_hor(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.x = b.x > 0.0f ? math_fl(a.x + 1.0f) : math_cl(a.x - 1.0f);
	c.y = v2_slope(b) * (c.x - a.x) + a.y;
	return (c);
}

inline t_v2		v2_steps_ver(t_v2 a, t_v2 b)
{
	t_v2 c;

	c.y = b.y > 0.0f ? math_fl(a.y + 1.0f) : math_cl(a.y - 1.0f);
	c.x = (c.y - a.y) / v2_slope(b) + a.x;
	return (c);
}

inline float	math_dec(const float x)
{
	return (x - (int)x);
}

inline float	v2_pcast(float size, int yres, int y)
{
	return (size / (2 * (y + 1) - yres));
}

inline t_line	line_rotate(const t_line l, const float t)
{
	t_line line;

	line.a = v2_turn(l.a, t);
	line.b = v2_turn(l.b, t);
	return (line);
}

inline t_v2		line_lerp(const t_line l, const float n)
{
	return (v2_add(l.a, v2_mul(v2_sub(l.b, l.a), n)));
}
