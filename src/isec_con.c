/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isec_con.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:02:04 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/11 00:02:35 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_con_formula(float *discr, t_vec3 *k, t_trc trc, t_fig *con)
{
	t_vec3	v;
	t_vec3	oc;

	v = div_vec3f(con->dir, len_vec3(con->dir));
	oc = minus_vec3(trc.o, con->pos);
	k->x = dot(trc.d, trc.d) - con->rad * pow(dot(trc.d, con->dir), 2);
	k->y = 2 * (dot(oc, trc.d) - con->rad * dot(trc.d, con->dir)
		* dot(oc, con->dir));
	k->z = dot(oc, oc) - con->rad * pow(dot(oc, con->dir), 2);
	*discr = k->y * k->y - 4 * k->x * k->z;
}

/*
** intersection with hyper_conus
*/

void	intersec_con(t_lst *lst, t_hit *hit, t_trc trc, t_fig *con)
{
	t_vec3	k;
	float	discr;
	float	t;

	get_con_formula(&discr, &k, trc, con);
	if (discr < 0)
		return ;
	discr = sqrt(discr);
	k.x *= 2;
	t = (discr - k.y) / k.x;
	hit->isec1 = get_isec_cyl(lst, trc, t, con);
	if (hit->isec1)
		hit->count = 1;
	if (discr == 0)
		return ;
	t = (-discr - k.y) / k.x;
	if (hit->isec1)
	{
		if ((hit->isec2 = get_isec_cyl(lst, trc, t, con)))
			hit->count = 2;
	}
	else if ((hit->isec1 = get_isec_cyl(lst, trc, t, con)))
		hit->count = 1;
}
