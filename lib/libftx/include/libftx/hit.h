/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftx/hit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_HIT_H
# define LIBFTX_HIT_H

# include "point.h"

typedef struct	s_hit
{
	int			tile;
	t_v2		where;
}				t_hit;

extern t_hit	ftx_hitcast(t_v2 w, t_v2 dir, char const **walling);

#endif
