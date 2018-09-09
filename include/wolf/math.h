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
# include <libft.h>

typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

typedef struct	s_hit
{
	int			tile;
	t_v2		where;
	int			hor;
	float		step;
}				t_hit;

typedef struct	s_line
{
	t_v2		a;
	t_v2		b;
}				t_line;

extern int		math_fl(float x);
extern int		math_cl(float x);
extern int		math_isfl(float x);
extern float	math_dec(float x);
extern t_v2		v2_turn(t_v2 a, float t);
extern t_v2		v2_rag(t_v2 a);
extern t_v2		v2_sub(t_v2 a, t_v2 b);
extern t_v2		v2_add(t_v2 a, t_v2 b);
extern float	v2_dist(t_v2 a, t_v2 b);
extern t_v2		v2_mul(t_v2 a, float n);
extern float	v2_mag(t_v2 a);
extern t_v2		v2_unit(t_v2 a);
extern float	v2_slope(t_v2 a);
extern t_v2		v2_steps_hor(t_v2 a, t_v2 b);
extern t_v2		v2_steps_ver(t_v2 a, t_v2 b);
extern float	v2_pcast(float size, int yres, int y);
extern t_line	line_rotate(t_line l, float t);
extern t_v2		ln_lerp(t_line l, float n);

#endif
