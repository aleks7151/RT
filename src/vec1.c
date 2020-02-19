/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:39:18 by vkaron            #+#    #+#             */
/*   Updated: 2020/01/14 15:00:02 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3 dst;

	dst.x = v1.y * v2.z - v1.z * v2.y;
	dst.y = v1.z * v2.x - v1.x * v2.z;
	dst.z = v1.x * v2.y - v1.y * v2.x;
	return (dst);
}

float		len_vec3(t_vec3 v)
{
	float len;

	len = sqrt(dot(v, v));
	return (len);
}

t_vec3		set_vec3(t_vec3 src)
{
	t_vec3 dst;

	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
	return (dst);
}

SDL_Color	set_col(int r, int g, int b, int a)
{
	SDL_Color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

t_vec3		cre_vec3(float x, float y, float z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0;
	return (v);
}
