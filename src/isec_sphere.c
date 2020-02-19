/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isec_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:42:47 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:30:31 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_inv_surf1(t_lst *lst, t_hit *h, t_fig *fig)
{
	h->isec1->fig = fig;
	h->count = 1;
	if (!lst->scn->inv_surf)
	{
		free(h->isec1);
		h->isec1 = NULL;
		h->count = 0;
	}
}

void	set_isec1_sph(t_hit *h, t_trc t, t_fig *s, float tr)
{
	float x;

	if (!(h->isec1 = malloc(sizeof(t_isec))))
		ft_exit("Not malloc");
	h->isec1->fig = s;
	h->isec1->t = tr;
	t.p = minus_vec3(s->pos, plus_vec3(t.o, mult_vec3f(t.d, h->isec1->t)));
	t.p = div_vec3f(t.p, len_vec3(t.p));
	x = -dot(s->dir, t.p);
	h->isec1->uv.y = acos(x);
	x = sin(h->isec1->uv.y);
	h->isec1->uv.x = (acos(dot(t.p, s->look) / x)) / (2 * M_PI);
	if (dot(s->right, t.p) > 0)
		h->isec1->uv.x = 1.0 - h->isec1->uv.x;
	h->isec1->uv.y = h->isec1->uv.y / M_PI;
	h->isec1->n2 = set_vec3(t.p);
	if (dot(t.d, t.p) < 0)
		h->isec1->n = set_vec3(t.p);
	else
		h->isec1->n = invert_vec3(t.p);
	h->count = 1;
}

void	set_inv_surf2(t_lst *lst, t_hit *h, t_fig *fig)
{
	h->isec2->fig = fig;
	h->count = 1;
	if (h->isec1)
		h->count = 2;
	if (!lst->scn->inv_surf)
	{
		free(h->isec2);
		h->isec2 = NULL;
		h->count = 0;
		if (h->isec1)
			h->count = 1;
	}
}

void	set_isec2_sph(t_hit *h, t_trc t, t_fig *s, float tr)
{
	float x;

	if (!(h->isec2 = malloc(sizeof(t_isec))))
		ft_exit("Not malloc");
	h->isec2->fig = s;
	h->isec2->t = tr;
	t.p = minus_vec3(s->pos, plus_vec3(t.o, mult_vec3f(t.d, h->isec2->t)));
	t.p = div_vec3f(t.p, len_vec3(t.p));
	x = -dot(s->dir, t.p);
	h->isec2->uv.y = acos(x);
	x = sin(h->isec2->uv.y);
	h->isec2->uv.x = (acos(dot(t.p, s->look) / x)) / (2 * M_PI);
	if (dot(s->right, t.p) > 0)
		h->isec2->uv.x = 1.0 - h->isec2->uv.x;
	h->isec2->uv.y = h->isec2->uv.y / M_PI;
	h->isec2->n2 = set_vec3(t.p);
	if (dot(t.d, t.p) < 0)
		h->isec2->n = set_vec3(t.p);
	else
		h->isec2->n = invert_vec3(t.p);
	h->count = 2;
}

/*
** intersection with sphere
*/

void	intersec_sph(t_lst *lst, t_hit *h, t_trc trc, t_fig *sph)
{
	t_vec3	oc;
	t_vec3	k;
	float	discr;
	float	t;

	oc = minus_vec3(trc.o, sph->pos);
	k.x = dot(trc.d, trc.d);
	k.y = dot(oc, trc.d);
	k.z = dot(oc, oc) - sph->rad * sph->rad;
	discr = k.y * k.y - k.x * k.z;
	if (discr < 0)
		return ;
	discr = sqrt(discr);
	t = (discr - k.y) / k.x;
	if ((h->isec1 = check_inv_figs(lst, trc, t)))
		set_inv_surf1(lst, h, sph);
	else
		set_isec1_sph(h, trc, sph, t);
	if (discr == 0)
		return ;
	t = (-discr - k.y) / k.x;
	if ((h->isec2 = check_inv_figs(lst, trc, t)))
		set_inv_surf2(lst, h, sph);
	else
		set_isec2_sph(h, trc, sph, t);
}
