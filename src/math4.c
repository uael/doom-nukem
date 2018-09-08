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

inline t_v2		ln_lerp(t_line l, float n)
{
	return (v2_add(l.a, v2_mul(v2_sub(l.b, l.a), n)));
}
