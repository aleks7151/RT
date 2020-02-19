/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isec_cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:59:41 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:28:51 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_isec	*ret_inv_isec(t_lst *lst, t_isec *isec, t_fig *fig)
{
	isec->fig = fig;
	if (!lst->scn->inv_surf)
	{
		free(isec);
		isec = NULL;
	}
	return (isec);
}

t_isec	*ret_cyl_con_isec(t_trc trc, t_fig *cyl, float t, float m)
{
	t_isec	*isec;
	t_vec3	p;
	t_vec3	dir;

	dir = mult_vec3f(cyl->dir, -1);
	if (!(isec = malloc(sizeof(t_isec))))
		ft_exit("Not malloc");
	isec->fig = cyl;
	isec->t = t;
	p = plus_vec3(mult_vec3f(trc.d, isec->t), trc.o);
	isec->n = minus_vec3(minus_vec3(p, cyl->pos), mult_vec3f(dir, m));
	isec->n2 = set_vec3(isec->n);
	if (dot(trc.d, isec->n) > 0)
		isec->n = invert_vec3(isec->n);
	isec->n = div_vec3f(isec->n, len_vec3(isec->n));
	isec->uv.x = (acos(dot(cyl->look, isec->n)) / (2 * M_PI));
	m *= 0.1;
	m -= (int)m;
	if (m < 0.0)
		m = -m;
	isec->uv.y = m;
	if (dot(cyl->right, isec->n) > 0)
		isec->uv.x = 1.0 - isec->uv.x;
	return (isec);
}

t_isec	*get_isec_cyl(t_lst *lst, t_trc trc, float t, t_fig *cyl)
{
	t_isec	*isec;
	t_vec3	dir;
	t_vec3	vt;
	float	m;

	dir = mult_vec3f(cyl->dir, -1);
	vt = mult_vec3f(dir, t);
	m = dot(trc.d, vt) + dot(dir, minus_vec3(trc.o, cyl->pos));
	if (cyl->limit.x == 0 || (m >= 0 && m <= cyl->limit.x))
	{
		if ((isec = check_inv_figs(lst, trc, t)))
			return (ret_inv_isec(lst, isec, cyl));
		return (ret_cyl_con_isec(trc, cyl, t, m));
	}
	return (NULL);
}

void	get_cyl_formula(float *discr, t_vec3 *k, t_trc trc, t_fig *cyl)
{
	t_vec3	v;
	t_vec3	oc;

	v = div_vec3f(cyl->dir, len_vec3(cyl->dir));
	oc = minus_vec3(trc.o, cyl->pos);
	k->x = dot(trc.d, trc.d) - pow(dot(trc.d, cyl->dir), 2);
	k->y = 2 * (dot(oc, trc.d) - dot(trc.d, cyl->dir) * dot(oc, cyl->dir));
	k->z = dot(oc, oc) - pow(dot(oc, cyl->dir), 2) - cyl->rad * cyl->rad;
	*discr = k->y * k->y - 4 * k->x * k->z;
}

/*
** intersection with hyper_cylinder
*/

void	intersec_cyl(t_lst *lst, t_hit *hit, t_trc trc, t_fig *cyl)
{
	t_vec3	k;
	float	discr;
	float	t;

	get_cyl_formula(&discr, &k, trc, cyl);
	if (discr < 0)
		return ;
	discr = sqrt(discr);
	k.x *= 2;
	t = (discr - k.y) / k.x;
	hit->isec1 = get_isec_cyl(lst, trc, t, cyl);
	if (hit->isec1)
		hit->count = 1;
	if (discr == 0)
		return ;
	t = (-discr - k.y) / k.x;
	if (hit->isec1)
	{
		if ((hit->isec2 = get_isec_cyl(lst, trc, t, cyl)))
			hit->count = 2;
	}
	else if ((hit->isec1 = get_isec_cyl(lst, trc, t, cyl)))
		hit->count = 1;
}
