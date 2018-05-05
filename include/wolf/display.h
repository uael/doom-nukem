/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf/display.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_DISPLAY_H
# define WOLF_DISPLAY_H

# include "game.h"

typedef struct		s_display
{
	uint32_t		*pixels;
	int				size;
}					t_display;

extern t_display	wl_lock(t_wl *wl);
extern void			wl_put(t_display display, int x, int y, uint32_t color);
extern void			wl_render(t_wl *wl);

#endif
