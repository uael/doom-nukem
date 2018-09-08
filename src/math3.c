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
