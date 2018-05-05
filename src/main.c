/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int	main(int ac, char *av[])
{
	t_wl			wl;
	uint8_t const	*keyboard;

	(void) ac;
	(void) av;
	wl_init(&wl, 1920, 1080);
    init_hero(&wl.hero, 0.8f);
	while(!wl_isdone(&wl))
	{
		keyboard = SDL_GetKeyboardState(NULL);
		wl_handle(&wl, keyboard);
	}
	return (EXIT_FAILURE);
}