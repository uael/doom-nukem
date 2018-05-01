/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/math/v3.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 10:28:45 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:34:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_V3_H
# define LIBFT_MATH_V3_H

# include <math.h>

# include "v2.h"

typedef float t_v3[3];

static inline void ft_v3_add(t_v3 r, t_v3 const a, t_v3 const b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] + b[i];
}

static inline void ft_v3_sub(t_v3 r, t_v3 const a, t_v3 const b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] - b[i];
}

static inline void ft_v3_scale(t_v3 r, t_v3 const v, float const s)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = v[i] * s;
}

static inline float ft_v3_mul_inner(t_v3 const a, t_v3 const b)
{
	float p;
	int i;

	p = 0.f;
	for (i = 0; i < 2; ++i)p += b[i] * a[i];
	return p;
}

static inline float ft_v3_len(t_v3 const v)
{
	return sqrtf(ft_v3_mul_inner(v, v));
}

static inline void ft_v3_norm(t_v3 r, t_v3 const v)
{
	float k;

	k = (float)(1.0 / ft_v3_len(v));
	ft_v3_scale(r, v, k);
}

static inline void ft_v3_min(t_v3 r, t_v3 a, t_v3 b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] < b[i] ? a[i] : b[i];
}

static inline void ft_v3_max(t_v3 r, t_v3 a, t_v3 b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] > b[i] ? a[i] : b[i];
}

#endif
