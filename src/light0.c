/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:24:10 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/09 18:24:11 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		refl_r(t_vec3 l, t_vec3 n)
{
	float	k;
	t_vec3	r;

	k = 2 * dot(n, l);
	r.x = k * n.x - l.x;
	r.y = k * n.y - l.y;
	r.z = k * n.z - l.z;
	return (r);
}

SDL_Color	get_color_from_file2(t_map map, t_vec3 uv)
{
	int			index_x;
	int			index_y;
	int			index;
	int			c;
	SDL_Color	res;

	index_x = (uv.x) * map.map->w;
	index_y = (uv.y) * map.map->h;
	index = clamp(index_x + index_y * map.map->w, 0, map.map->w * map.map->h);
	c = map.data[index];
	res.r = clamp((c & 0xff0000) >> 16, 0, 255);
	res.g = clamp((c & 0xff00) >> 8, 0, 255);
	res.b = clamp(c & 0xff, 0, 255);
	return (res);
}

/*
** check shadow for current point or directional light
*/

t_vec3		transpare_shadow(t_isec *shdw, t_vec3 kof)
{
	float		tr;
	float		transp;
	SDL_Color	col;

	if (!shdw)
		return (kof);
	else if (shdw->fig->mat->transpare == 0)
		return (cre_vec3(0, 0, 0));
	col.r = shdw->fig->mat->col.r;
	col.g = shdw->fig->mat->col.g;
	col.b = shdw->fig->mat->col.b;
	if (shdw->fig->mat->diff_map.map && shdw->uv.x && shdw->uv.x != INFINITY)
		col = get_color_from_file2(shdw->fig->mat->diff_map, shdw->uv);
	if (shdw->fig->mat->mask_map.map && shdw->uv.x && shdw->uv.x != INFINITY)
		transp = get_transp_from_file(shdw->fig->mat->mask_map, shdw->uv);
	else
		transp = shdw->fig->mat->transpare;
	tr = ((transp) * 2 - 1.0) * 255;
	col.r = clamp(tr + col.r, 0, 255) * (transp);
	col.g = clamp(tr + col.g, 0, 255) * (transp);
	col.b = clamp(tr + col.b, 0, 255) * (transp);
	kof.x = clampf(kof.x - 0.9 + (float)col.r / 255.0, 0, kof.x);
	kof.y = clampf(kof.y - 0.9 + (float)col.g / 255.0, 0, kof.y);
	kof.z = clampf(kof.z - 0.9 + (float)col.b / 255.0, 0, kof.z);
	return (transpare_shadow(shdw->next, kof));
}

void		trc_init(t_trc *trc, t_lght *c_lght, t_l_prm b)
{
	trc->d.x = c_lght->pos.x - b.p.x;
	trc->d.y = c_lght->pos.y - b.p.y;
	trc->d.z = c_lght->pos.z - b.p.z;
	trc->max = 1;
}

t_trc		get_all_really(t_vec3 *ints, t_l_prm b, t_lght **c_lght, int check)
{
	t_trc trc;

	if (check)
	{
		*ints = cre_vec3(0, 0, 0);
		trc.min = MIN_OFFSET;
		trc.o = set_vec3(b.p);
	}
	else
	{
		*c_lght = (*c_lght)->next;
		trc.min = 1;
	}
	return (trc);
}
