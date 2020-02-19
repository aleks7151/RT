/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bgc_mixcol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:12:28 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/11 20:51:16 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** set parametr for call light function
*/

SDL_Color	mix_color(SDL_Color c1, SDL_Color c2, float koef)
{
	SDL_Color	res;
	float		akoef;

	koef = clampf(koef, 0, 1);
	akoef = 1.0 - koef;
	res.r = clamp(c1.r * koef + c2.r * akoef, 0, 255);
	res.g = clamp(c1.g * koef + c2.g * akoef, 0, 255);
	res.b = clamp(c1.b * koef + c2.b * akoef, 0, 255);
	return (res);
}

void		return_background0(t_vec3 *xuv, t_trc trc)
{
	t_vec3		dt;

	dt = div_vec3f(trc.d, len_vec3(trc.d));
	xuv->x = dot((t_vec3){0, 0.9999, 0, 0}, dt);
	xuv->y = acos(xuv->x);
	xuv->x = sin(acos(xuv->x));
	xuv->z = (acos(dot(dt, (t_vec3){0, 0, 1, 0}) / xuv->x)) / (2 * M_PI);
	if (dot(cross((t_vec3){0, 0.9999, 0, 0}, (t_vec3){0, 0, 1, 0}), dt) > 0)
		xuv->z = 1.0 - xuv->z;
	xuv->y = xuv->y / M_PI;
}

SDL_Color	return_background(t_lst *lst, t_trc trc)
{
	SDL_Color	res;
	t_vec3		xuv;
	int			index;

	if (lst->shd && lst->scn->fog.enable && lst->scn->fog.max_tr == 0)
		return (lst->scn->fog.col);
	if ((lst->shd && !lst->scn->diff_map.map) || !lst->shd)
	{
		if (lst->shd && lst->scn->fog.enable)
			return (mix_color(lst->scn->bgc,
		lst->scn->fog.col, lst->scn->fog.max_tr));
		else
			return (lst->scn->bgc);
	}
	return_background0(&xuv, trc);
	index = clamp((int)(xuv.z * lst->scn->diff_map.map->w) + (int)(xuv.y *
		lst->scn->diff_map.map->h) * lst->scn->diff_map.map->w, 0,
		lst->scn->diff_map.map->w * lst->scn->diff_map.map->h);
	index = lst->scn->diff_map.data[index];
	res.r = clamp(((index & 0xff0000) >> 16), 0, 255);
	res.g = clamp(((index & 0xff00) >> 8), 0, 255);
	res.b = clamp((index & 0xff), 0, 255);
	if (lst->scn->fog.enable)
		return (mix_color(res, lst->scn->fog.col, lst->scn->fog.max_tr));
	return (res);
}
