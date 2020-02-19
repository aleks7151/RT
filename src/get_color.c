/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:01:15 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/12 21:46:04 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Color	mult_sdl_color(SDL_Color col, float koef)
{
	SDL_Color res;

	res.r = clamp(col.r * koef, 0, 255);
	res.g = clamp(col.g * koef, 0, 255);
	res.b = clamp(col.b * koef, 0, 255);
	return (res);
}

SDL_Color	mult_int_color(int c, float koef)
{
	SDL_Color res;

	res.r = clamp(((c & 0xff0000) >> 16) * koef, 0, 255);
	res.g = clamp(((c & 0xff00) >> 8) * koef, 0, 255);
	res.b = clamp((c & 0xff) * koef, 0, 255);
	return (res);
}

SDL_Color	plus_sdl_color(SDL_Color col1, SDL_Color col2)
{
	SDL_Color res;

	res.r = clamp(col1.r + col2.r, 0, 255);
	res.g = clamp(col1.g + col2.g, 0, 255);
	res.b = clamp(col1.b + col2.b, 0, 255);
	return (res);
}

t_l_prm		set_l_prm(t_trc trc, t_vec3 n)
{
	t_l_prm b;

	b.n = set_vec3(n);
	b.p = set_vec3(trc.p);
	b.v = set_vec3(trc.d);
	return (b);
}

void		get_normal_from_file(t_isec *cisec)
{
	t_vec3		norm;
	SDL_Rect	size;
	SDL_Rect	index;
	uint		n;

	size.w = cisec->fig->mat->norm_map.map->w;
	size.h = cisec->fig->mat->norm_map.map->h;
	index.x = cisec->uv.x * size.w;
	index.y = cisec->uv.y * size.h;
	index.w = clamp((int)(index.x + index.y * size.w),
		0, size.w * size.h);
	n = cisec->fig->mat->norm_map.data[(int)index.w];
	norm.x = 0.5 - ((n & 0xff0000) >> 16) / 255.0f;
	norm.y = 0.5 - ((n & 0xff00) >> 8) / 255.0f;
	norm.z = 1.0 - (n & 0xff) / 255.0f;
	cisec->n = minus_vec3(cisec->n, norm);
	cisec->n = div_vec3f(cisec->n, len_vec3(cisec->n));
}
