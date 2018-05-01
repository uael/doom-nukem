/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftx/point.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_POINT_H
# define LIBFTX_POINT_H

# include <libft.h>

typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

/*
** @brief
 * Rotates the vector by some radian value.
 *
** @param a The vector to rotate.
** @param t The angle in radian.
** @return  The new rotated vector.
*/
extern t_v2		ftx_v2turn(t_v2 a, float t);

/*
** 
** @param a 
** @return 
*/
extern t_v2		ftx_v2rag(t_v2 a);

/*
** 
** @param a 
** @param b 
** @return 
*/
extern t_v2		ftx_v2sub(t_v2 a, t_v2 b);

/*
** 
** @param a 
** @param b 
** @return 
*/
extern t_v2		ftx_v2add(t_v2 a, t_v2 b);


/*
** 
** @param a 
** @param n 
** @return 
*/
extern t_v2		ftx_v2mul(t_v2 a, float n);

/*
** 
** @param a 
** @return 
*/
extern float	ftx_v2mag(t_v2 a);

/*
** 
** @param a 
** @return 
*/
extern t_v2		ftx_v2unit(t_v2 a);

/*
** 
** @param a 
** @return 
*/
extern float	ftx_v2slope(t_v2 a);

/*
** 
** @param a 
** @param b 
** @return 
*/
extern t_v2		ftx_v2sh(t_v2 a, t_v2 b);

/*
** 
** @param a 
** @param b 
** @return 
*/
extern t_v2		ftx_v2sv(t_v2 a, t_v2 b);

#endif
