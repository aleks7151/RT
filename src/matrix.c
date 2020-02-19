/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:10:09 by vkaron            #+#    #+#             */
/*   Updated: 2020/01/09 18:24:17 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_m4_rz(t_mat3 *m, float fi)
{
	float	s;
	float	c;

	s = sin(fi * M_PI / 180);
	c = cos(fi * M_PI / 180);
	m->f1.x = c;
	m->f1.y = -s;
	m->f1.z = 0;
	m->f2.x = s;
	m->f2.y = c;
	m->f2.z = 0;
	m->f3.x = 0;
	m->f3.y = 0;
	m->f3.z = 1;
}

void	set_m4_rx(t_mat3 *m, float fi)
{
	float	s;
	float	c;

	s = sin(fi * M_PI / 180);
	c = cos(fi * M_PI / 180);
	m->f1.x = 1;
	m->f1.y = 0;
	m->f1.z = 0;
	m->f2.x = 0;
	m->f2.y = c;
	m->f2.z = -s;
	m->f3.x = 0;
	m->f3.y = s;
	m->f3.z = c;
}

void	set_m4_ry(t_mat3 *m, float fi)
{
	float	s;
	float	c;

	s = sin(fi * M_PI / 180);
	c = cos(fi * M_PI / 180);
	m->f1.x = c;
	m->f1.y = 0;
	m->f1.z = s;
	m->f2.x = 0;
	m->f2.y = 1;
	m->f2.z = 0;
	m->f3.x = -s;
	m->f3.y = 0;
	m->f3.z = c;
}

void	mult_m3(t_vec3 *d, t_vec3 s, t_mat3 m)
{
	d->x = s.x * m.f1.x + s.y * m.f1.y + s.z * m.f1.z;
	d->y = s.x * m.f2.x + s.y * m.f2.y + s.z * m.f2.z;
	d->z = s.x * m.f3.x + s.y * m.f3.y + s.z * m.f3.z;
}
