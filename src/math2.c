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

inline float	v2_dist(t_v2 a, t_v2 b)
{
	return (sqrtf(powf(b.x - a.x, 2) + powf(b.y - a.y, 2)));
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
