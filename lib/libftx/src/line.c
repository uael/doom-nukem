/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftx/line.h"

inline t_ln		ftx_lnviewport(float focal)
{
	return ((t_ln){ { focal, -1.0f }, { focal, +1.0f } });
}

inline t_v2		ftx_lnlerp(t_ln l, float n)
{
	return ftx_v2add(l.a, ftx_v2mul(ftx_v2sub(l.b, l.a), n));
}

inline t_ln		ftx_lnrot(t_ln l, float t)
{
	return ((t_ln){ ftx_v2turn(l.a, t), ftx_v2turn(l.b, t) });
}
