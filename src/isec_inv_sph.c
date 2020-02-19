/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isec_inv_sph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:55:07 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:29:46 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_isec	*set_isec_inv_sph(t_trc trc, t_fig *isph, float p)
{
	t_isec	*isec;

	if (!(isec = malloc(sizeof(t_isec))))
		ft_exit("Not malloc");
	isec->t = p;
	trc.p = minus_vec3(isph->pos, plus_vec3(trc.o, mult_vec3f(trc.d, isec->t)));
	trc.p = div_vec3f(trc.p, len_vec3(trc.p));
	isec->uv.y = acos(-dot(isph->dir, trc.p));
	isec->uv.x = (acos(dot(trc.p, isph->look) / sin(isec->uv.y))) / (2 * M_PI);
	if (dot(isph->right, trc.p) > 0)
		isec->uv.x = 1.0 - isec->uv.x;
	isec->uv.y = isec->uv.y / M_PI;
	if (dot(trc.d, trc.p) < 0)
		isec->n = invert_vec3(trc.p);
	else
		isec->n = set_vec3(trc.p);
	isec->n2 = set_vec3(isec->n);
	return (isec);
}

t_isec	*check_inv_sph(t_trc trc, float t, t_fig *isph)
{
	t_vec3	oc;
	t_vec3	k;
	float	discr;
	float	p;

	trc.p = plus_vec3(trc.o, mult_vec3f(trc.d, t));
	if (len_vec3(minus_vec3(isph->pos, trc.p)) > isph->rad)
		return (NULL);
	oc = minus_vec3(trc.o, isph->pos);
	k.x = dot(trc.d, trc.d);
	k.y = dot(oc, trc.d);
	k.z = dot(oc, oc) - isph->rad * isph->rad;
	discr = k.y * k.y - k.x * k.z;
	if (discr < 0)
		return (NULL);
	discr = sqrt(discr);
	k.x = 1 / k.x;
	p = (-discr - k.y) * k.x;
	if (p > t)
		return (NULL);
	return (set_isec_inv_sph(trc, isph, p));
}

t_isec	*check_inv_figs(t_lst *lst, t_trc trc, float t)
{
	t_fig	*cur_fig;
	t_isec	*isec;

	isec = NULL;
	cur_fig = lst->scn->figs;
	while (cur_fig)
	{
		if (cur_fig->type == inv_sph)
		{
			if ((isec = check_inv_sph(trc, t, cur_fig)))
				return (isec);
		}
		cur_fig = cur_fig->next;
	}
	return (NULL);
}
