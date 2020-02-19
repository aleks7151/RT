/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:30:06 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 18:47:58 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Color	get_color_from_file(t_map map, t_vec3 uv, t_vec3 l)
{
	int				index_x;
	int				index_y;
	unsigned int	index;
	int				c;
	SDL_Color		res;

	index_x = (uv.x) * map.map->w;
	index_y = (uv.y) * map.map->h;
	index = clamp(index_x + index_y * map.map->w, 1,
		map.map->w * map.map->h - 1);
	c = map.data[index];
	res.r = clamp(((c & 0xff0000) >> 16) * l.x, 0, 255);
	res.g = clamp(((c & 0xff00) >> 8) * l.y, 0, 255);
	res.b = clamp((c & 0xff) * l.z, 0, 255);
	return (res);
}

float		get_transp_from_file(t_map map, t_vec3 uv)
{
	int		index_x;
	int		index_y;
	int		index;
	int		c;
	float	res;

	index_x = (uv.x) * map.map->w;
	index_y = (uv.y) * map.map->h;
	index = clamp(index_x + index_y * map.map->w, 0, map.map->w * map.map->h);
	c = map.data[index];
	res = 1.0 - clamp(((c & 0xff)), 0, 255) / 255.0;
	if (res > 0.5)
		res = 1;
	return (res);
}

void		free_isec_list(t_isec *cisec)
{
	t_isec	*tmp;

	while (cisec)
	{
		tmp = cisec;
		cisec = cisec->next;
		free(tmp);
	}
}

/*
** ray trace function
*/

void		cycle_trace(t_lst *l, t_trc *trc,
	t_isec *ci, SDL_Color *c)
{
	t_vec3 lt;

	trc->p = plus_vec3(mult_vec3f(trc->d, ci->t), (trc->o));
	if (l->shd && ci->fig->mat->norm_map.map && ci->uv.x && ci->uv.x != INFY)
		get_normal_from_file(ci);
	trc->d = invert_vec3(trc->d);
	lt = light(l, set_l_prm(*trc, ci->n), ci->fig, l->scn->lghts);
	if (l->shd && ci->fig->mat->diff_map.map && ci->uv.x && ci->uv.x != INFY)
		*c = get_color_from_file(ci->fig->mat->diff_map, ci->uv, lt);
	else
	{
		c->r = clamp(ci->fig->mat->col.r * lt.x, 0, 255);
		c->g = clamp(ci->fig->mat->col.g * lt.y, 0, 255);
		c->b = clamp(ci->fig->mat->col.b * lt.z, 0, 255);
	}
	if (!l->shd && l->scn->fog.enable)
		*c = mix_color(l->scn->fog.col, *c, ci->t / l->scn->fog.near);
	trc->o = set_vec3(trc->p);
	if (l->shd >= REFRLECT && l->depth > 0 && ci->fig->mat->refl > 0)
		*c = plus_sdl_color(mult_sdl_color(*c, 1.0 - ci->fig->mat->refl),
			mult_sdl_color(get_refl_col(l, *trc,
			ci->n, l->depth - 1), ci->fig->mat->refl));
	if (l->shd >= REFRACT && l->depth_refr)
		check_refr(l, trc, ci, c);
}

SDL_Color	trace(t_lst *l, t_trc trc, int dep, t_isec *csc)
{
	SDL_Color	res;
	t_vec3		fkt;
	SDL_Color	tres;
	t_isec		*c_isc;
	SDL_Color	col;

	if (find_me_clrs(&csc, l, trc, &col))
		return (col);
	c_isc = csc;
	init_trace0(l, dep, &fkt, &res);
	while (c_isc)
	{
		if (l->shd && c_isc->fig->mat->mask_map.map
			&& c_isc->uv.x && c_isc->uv.x != INFY)
			fkt.z = get_transp_from_file(c_isc->fig->mat->mask_map,
				c_isc->uv);
		else
			fkt.z = c_isc->fig->mat->transpare;
		if (fkt.z < 1.0)
			cycle_trace(l, &trc, c_isc, &tres);
		if (idono(&fkt, &res, tres, &c_isc) || l->shd < TRASPARENT)
			break ;
	}
	l->res_help = res;
	return (return_trace(l, fkt, col, &csc));
}
