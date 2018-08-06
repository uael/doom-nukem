/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

static inline char	hswap(t_map *self, char *key, char *val, uint32_t i)
{
	(void)self;
	(void)key;
	(void)val;
	(void)i;
	return (0);
}

static inline void	reh1(t_map *self, uint32_t sz, uint8_t *bucks, uint32_t j)
{
	(void)self;
	(void)sz;
	(void)bucks;
	(void)j;
}

static inline void	reh(t_map *self, uint32_t sz, uint8_t *bucks)
{
	uint32_t j;

	j = 0;
	while (j != self->cap)
	{
		if (!(self->bucks[j] & BUCKET_BOTH))
			reh1(self, sz, bucks, (uint32_t)j);
		++j;
	}
	if (self->cap > sz)
	{
		self->keys = ft_realloc(self->keys, sz * self->ksz, sz * self->ksz);
		self->vals = ft_realloc(self->vals, sz * self->vsz, sz * self->vsz);
	}
	free(self->bucks);
	self->bucks = bucks;
	self->cap = sz;
	self->occupieds = self->len;
	self->upper_bound = (uint32_t)(self->cap * MAP_HASH_UPPER + 0.5);
}

size_t				ft_maprsz(t_map *self, uint32_t sz)
{
	uint8_t		*bucks;
	uint32_t	j;

	j = 1;
	bucks = NULL;
	if ((sz = pow2_next32(sz)) < 32)
		sz = 32;
	if (self->len >= (uint32_t)(sz * MAP_HASH_UPPER + 0.5))
		j = 0;
	else if ((bucks = (uint8_t *)ft_malloc(sz)))
	{
		ft_memset(bucks, BUCKET_EMPTY, sz);
		if (self->cap < sz)
		{
			self->keys = ft_realloc(self->keys, self->cap * self->ksz,
				sz * self->ksz);
			self->vals = ft_realloc(self->vals, self->cap * self->vsz,
				sz * self->vsz);
		}
	}
	if (j)
		reh(self, sz, bucks);
	return (self->cap);
}
