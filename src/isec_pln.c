/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isec_pln.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:03:35 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:30:02 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_isec1_pln(t_hit *h, t_trc trc, t_fig *pln, t_trc t)
{
	t_vec3	uv;

	uv = t.o;
	if (!(h->isec1 = malloc(sizeof(t_isec))))
		ft_exit("Not malloc");
	h->isec1->fig = pln;
	h->isec1->t = t.min;
	h->isec1->n = set_vec3(t.d);
	h->isec1->n2 = invert_vec3(t.d);
	h->count = 1;
	uv.x -= (int)uv.x;
	uv.y -= (int)uv.y;
	if (uv.x < 0)
		uv.x = -uv.x;
	if (uv.y < 0)
		uv.y = -uv.y;
	if (dot(trc.p, pln->right) > 0)
		uv.x = 1.0 - uv.x;
	if (dot(trc.p, pln->look) < 0)
		uv.y = 1.0 - uv.y;
	h->isec1->uv.y = uv.y;
	h->isec1->uv.x = uv.x;
}

/*
** intersection with plane
*/

void	intersec_pln(t_lst *lst, t_hit *h, t_trc trc, t_fig *p)
{
	t_vec3	oc;
	t_trc	t;

	t.d = set_vec3(p->dir);
	if (dot(trc.d, t.d) > 0)
		t.d = invert_vec3(t.d);
	{
		oc = invert_vec3(minus_vec3(trc.o, p->pos));
		t.min = dot(oc, t.d) / dot(trc.d, t.d);
		trc.p = minus_vec3(p->pos, plus_vec3(trc.o, mult_vec3f(trc.d, t.min)));
		t.o.y = (dot(p->look, trc.p)) * 0.1;
		t.o.x = (dot(p->right, trc.p)) * 0.1;
		if ((t.o.x >= 0 && t.o.x <= p->limit.x && t.o.y >= 0
			&& t.o.y <= p->limit.y) || p->limit.x == 0 || p->limit.y == 0)
		{
			if ((h->isec1 = check_inv_figs(lst, trc, t.min)))
			{
				set_inv_surf1(lst, h, p);
				return ;
			}
			set_isec1_pln(h, trc, p, t);
		}
	}
}
