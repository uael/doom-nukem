/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf/game.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_MATH_H
# define WOLF_MATH_H

# include <math.h>
# include <stdint.h>

typedef struct	s_point
{
	double		x;
	double		y;
}				t_v2;

typedef struct	s_hit
{
	int			tile;
	t_v2		where;
}				t_hit;

typedef struct	s_line
{
	t_v2		a;
	t_v2		b;
}				t_line;

inline int		math_fl(double x);
inline int		math_cl(double x);
inline int		math_isfl(double x);
inline t_v2	v2_turn(t_v2 a, double t);
inline t_v2	v2_rag(t_v2 a);
inline t_v2	v2_sub(t_v2 a, t_v2 b);
inline t_v2	v2_add(t_v2 a, t_v2 b);
inline t_v2	v2_mul(t_v2 a, double n);
inline double	v2_mag(t_v2 a);
inline t_v2	v2_unit(t_v2 a);
inline double	point_slope(t_v2 a);
inline t_v2	point_sh(t_v2 a, t_v2 b);
inline t_v2	point_sv(t_v2 a, t_v2 b);
inline int		v2_tile(t_v2 a, const char **tiles);
inline double	math_dec(double x);
inline t_hit	v2_cast(t_v2 where, t_v2 dir, const char **walling);
inline double	point_pcast(double size, int yres, int y);
inline t_line	line_rotate(t_line l, double t);
inline t_v2	line_lerp(t_line l, double n);

#endif
