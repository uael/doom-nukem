/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/math/v2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 10:28:45 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:34:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_V2_H
# define LIBFT_MATH_V2_H

# include <math.h>

typedef float t_v2[2];

static inline void ft_v2_add(t_v2 r, t_v2 const a, t_v2 const b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] + b[i];
}

static inline void ft_v2_sub(t_v2 r, t_v2 const a, t_v2 const b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] - b[i];
}

static inline void ft_v2_scale(t_v2 r, t_v2 const v, float const s)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = v[i] * s;
}

static inline float ft_v2_mul_inner(t_v2 const a, t_v2 const b)
{
	float p;
	int i;

	p = 0.f;
	for (i = 0; i < 2; ++i)p += b[i] * a[i];
	return p;
}

static inline float ft_v2_len(t_v2 const v)
{
	return sqrtf(ft_v2_mul_inner(v, v));
}

static inline void ft_v2_norm(t_v2 r, t_v2 const v)
{
	float k;

	k = (float)(1.0 / ft_v2_len(v));
	ft_v2_scale(r, v, k);
}

static inline void ft_v2_min(t_v2 r, t_v2 a, t_v2 b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] < b[i] ? a[i] : b[i];
}

static inline void ft_v2_max(t_v2 r, t_v2 a, t_v2 b)
{
	int i;
	for (i = 0; i < 2; ++i)r[i] = a[i] > b[i] ? a[i] : b[i];
}

#endif
