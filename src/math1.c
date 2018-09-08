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
