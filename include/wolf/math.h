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

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_hit
{
	int			tile;
	t_point		where;
}				t_hit;

typedef struct	s_line
{
	t_point		a;
	t_point		b;
}				t_line;

inline int		math_fl(double x);
inline int		math_cl(double x);
inline t_point	point_turn(t_point a, double t);
inline t_point	point_rag(t_point a);
inline t_point	point_sub(t_point a, t_point b);
inline t_point	point_add(t_point a, t_point b);
inline t_point	point_mul(t_point a, double n);
inline double	point_mag(t_point a);
inline t_point	point_unit(t_point a);
inline double	point_slope(t_point a);
inline t_point	point_sh(t_point a, t_point b);
inline t_point	point_sv(t_point a, t_point b);
inline int		point_tile(t_point a, const char **tiles);
inline double	math_dec(double x);
inline t_hit	point_cast(t_point where, t_point dir, const char **walling);
inline double	point_pcast(double size, int yres, int y);
inline t_line	line_rotate(t_line l, double t);
inline t_point	line_lerp(t_line l, double n);

#endif
