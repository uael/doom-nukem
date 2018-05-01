/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftx/line.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_LINE_H
# define LIBFTX_LINE_H

# include "point.h"

typedef struct	s_ln
{
	t_v2		a;
	t_v2		b;
}				t_ln;

extern t_ln		ftx_lnviewport(float focal);
extern t_v2		ftx_lnlerp(t_ln line, float n);
extern t_ln		ftx_lnrot(t_ln line, float t);

#endif
