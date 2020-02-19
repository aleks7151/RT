/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:39:53 by vkaron            #+#    #+#             */
/*   Updated: 2020/01/09 18:24:48 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	minus_vec3(t_vec3 src1, t_vec3 src2)
{
	t_vec3 dst;

	dst.x = src1.x - src2.x;
	dst.y = src1.y - src2.y;
	dst.z = src1.z - src2.z;
	return (dst);
}

t_vec3	plus_vec3(t_vec3 src1, t_vec3 src2)
{
	t_vec3 dst;

	dst.x = src1.x + src2.x;
	dst.y = src1.y + src2.y;
	dst.z = src1.z + src2.z;
	return (dst);
}

t_vec3	mult_vec3f(t_vec3 src, float n)
{
	t_vec3 dst;

	dst.x = src.x * n;
	dst.y = src.y * n;
	dst.z = src.z * n;
	return (dst);
}

t_vec3	div_vec3f(t_vec3 src, float n)
{
	t_vec3	dst;

	dst.x = src.x / n;
	dst.y = src.y / n;
	dst.z = src.z / n;
	return (dst);
}

t_vec3	invert_vec3(t_vec3 src)
{
	t_vec3 dst;

	dst.x = 0 - src.x;
	dst.y = 0 - src.y;
	dst.z = 0 - src.z;
	return (dst);
}
