/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/math/v4.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 10:28:45 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:34:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_V4_H
# define LIBFT_MATH_V4_H

# include <math.h>

# include "v3.h"

typedef float t_v4[4];

static inline void ft_v4_add(t_v4 r, t_v4 const a, t_v4 const b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] + b[i];
}

static inline void ft_v4_sub(t_v4 r, t_v4 const a, t_v4 const b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] - b[i];
}

static inline void ft_v4_scale(t_v4 r, t_v4 const v, float const s)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = v[i] * s;
}

static inline float ft_v4_mul_inner(t_v4 const a, t_v4 const b)
{
	float p;
	int i;

	p = 0.f;
	for (i = 0; i < 2; ++i)p += b[i] * a[i];
	return p;
}

static inline float ft_v4_len(t_v4 const v)
{
	return sqrtf(ft_v4_mul_inner(v, v));
}

static inline void ft_v4_norm(t_v4 r, t_v4 const v)
{
	float k;

	k = (float)(1.0 / ft_v4_len(v));
	ft_v4_scale(r, v, k);
}

static inline void ft_v4_min(t_v4 r, t_v4 a, t_v4 b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] < b[i] ? a[i] : b[i];
}

static inline void ft_v4_max(t_v4 r, t_v4 a, t_v4 b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] > b[i] ? a[i] : b[i];
}

#endif
