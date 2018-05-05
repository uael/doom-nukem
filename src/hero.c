/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by nfinkel           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void    init_hero(t_hero *hero, const float focal)
{
    ft_bzero(hero, sizeof(t_hero));
    hero->fov = ftx_lnviewport(focal);
    hero->where = (t_v2){3.5f, 3.5f};
    hero->speed = 0.10f;
    hero->acceleration = 0.015f;
}