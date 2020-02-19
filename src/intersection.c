/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:12:56 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/11 00:05:05 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** selection figure for check
*/

void	transform_uv(t_isec *isec)
{
	t_uv	uvt;
	float	x;

	uvt = isec->fig->uvt;
	isec->uv.x = isec->uv.x * uvt.scale.x;
	isec->uv.y = isec->uv.y * uvt.scale.y;
	x = isec->uv.x;
	isec->uv.x = isec->uv.x * uvt.rot_tr.x - isec->uv.y * uvt.rot_tr.y;
	isec->uv.y = x * uvt.rot_tr.y + isec->uv.y * uvt.rot_tr.x;
	isec->uv.x = isec->uv.x + uvt.move.x;
	isec->uv.y = isec->uv.y + uvt.move.y;
	if (isec->uv.x > 1 || isec->uv.x < 0)
		isec->uv.x -= (int)(isec->uv.x);
	if (isec->uv.x < 0)
		isec->uv.x += 1.0;
	if (isec->uv.y > 1 || isec->uv.y < 0)
		isec->uv.y -= (int)(isec->uv.y);
	if (isec->uv.y < 0)
		isec->uv.y += 1.0;
}

void	check_count_isec(t_hit *hit)
{
	if (hit->isec1 && hit->isec2)
		hit->count = 2;
	else if (!hit->isec1 && !hit->isec2)
		hit->count = 0;
	else if (hit->isec1 && !hit->isec2)
		hit->count = 1;
	else
	{
		hit->isec1 = hit->isec2;
		hit->isec2 = NULL;
		hit->count = 1;
	}
	if (hit->isec1)
		transform_uv(hit->isec1);
}

void	check_isec(t_hit *h)
{
	float tr;

	if (h->isec1 && h->isec1->fig->mat && h->isec1->fig->mat->mask_map.map)
	{
		tr = get_transp_from_file(h->isec1->fig->mat->mask_map, h->isec1->uv);
		if (tr == 1)
		{
			free(h->isec1);
			h->isec1 = NULL;
		}
	}
	if (h->isec2 && h->isec2->fig->mat && h->isec2->fig->mat->mask_map.map)
	{
		tr = get_transp_from_file(h->isec2->fig->mat->mask_map, h->isec2->uv);
		if (tr == 1)
		{
			free(h->isec2);
			h->isec2 = NULL;
		}
	}
	check_count_isec(h);
}

void	sel_fig_check(t_lst *lst, t_hit *hit, t_trc trc, t_fig *cur_fig)
{
	hit->isec1 = NULL;
	hit->isec2 = NULL;
	hit->count = 0;
	if (cur_fig->type == sphere)
		intersec_sph(lst, hit, trc, cur_fig);
	else if (cur_fig->type == cylinder)
		intersec_cyl(lst, hit, trc, cur_fig);
	else if (cur_fig->type == conus)
		intersec_con(lst, hit, trc, cur_fig);
	else if (cur_fig->type == plane)
		intersec_pln(lst, hit, trc, cur_fig);
	if (hit->count && lst->scn->inv_surf == 0)
		check_isec(hit);
}
