/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_and_pp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:34:42 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/12 21:21:57 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		init_res(float x, float y, float z, float w)
{
	t_vec3 res_vec;

	res_vec.x = x;
	res_vec.y = y;
	res_vec.z = z;
	res_vec.w = w;
	return (res_vec);
}

SDL_Color	blur0(int *data, int k, float blur_x, float blur_y)
{
	t_vec3		t;
	t_vec3		res_vec;
	SDL_Color	res;

	res_vec = init_res(0, 0, 0, 0);
	t = init_res(0, blur_y, 0, 0);
	while (blur_y >= 0)
	{
		t.z = k + (t.y - blur_y) * 2 * S_W - 1;
		t.x = blur_x;
		while (t.x >= 0 && ++t.z < S_H * S_W && t.z <
		(int)((k + (t.y - blur_y) * 2 * S_W) / S_W) * S_W + S_W)
		{
			res_vec.x += (data[(int)t.z] & 0xff0000) >> 16;
			res_vec.y += (data[(int)t.z] & 0xff00) >> 8;
			res_vec.z += data[(int)t.z] & 0xff;
			t.w++;
			t.x -= 0.5;
		}
		blur_y -= 0.5;
	}
	res.r = res_vec.x / t.w;
	res.g = res_vec.y / t.w;
	res.b = res_vec.z / t.w;
	return (res);
}

SDL_Color	blur(int *data, int i, float blur_x, float blur_y)
{
	int			k;

	k = i - blur_x;
	while (k < i / S_W * S_W)
	{
		k++;
		blur_x -= 0.5;
	}
	k -= S_W * blur_y;
	while (k < 0)
	{
		k += S_W;
		blur_y -= 0.5;
	}
	return (blur0(data, k, blur_x, blur_y));
}

t_vec3		pixel_picture0(int *data, int i, int pix_x, int pix_y)
{
	t_vec3	res_vec;
	t_vec3	t;

	res_vec = init_res(0, 0, 0, 0);
	t.y = pix_y;
	while (pix_y > 0)
	{
		t.x = pix_x;
		t.z = i + (t.y - pix_y) * S_W;
		while (t.x > 0 && t.z < S_H * S_W && t.z <
		(int)((i + (t.y - pix_y) * S_W) / S_W) * S_W + S_W)
		{
			res_vec.x += (data[(int)t.z] & 0xff0000) >> 16;
			res_vec.y += (data[(int)t.z] & 0xff00) >> 8;
			res_vec.z += data[(int)t.z] & 0xff;
			t.z++;
			t.x--;
			res_vec.w++;
		}
		pix_y--;
	}
	return (res_vec);
}

SDL_Color	pixel_picture(int *data, int i, int pix_x, int pix_y)
{
	t_vec3		res_vec;
	SDL_Color	res;

	while (i / S_W % pix_y != 0)
		i -= S_W;
	while (i % pix_x != 0)
		i--;
	res_vec = pixel_picture0(data, i, pix_x, pix_y);
	res.r = res_vec.x / res_vec.w;
	res.g = res_vec.y / res_vec.w;
	res.b = res_vec.z / res_vec.w;
	return (res);
}
