/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_refl_refr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:58:06 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/12 21:47:55 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** calculate reflection color for dot
*/

SDL_Color	get_refl_col(t_lst *lst, t_trc trc, t_vec3 n, int depth)
{
	SDL_Color	refl_col;
	t_isec		*cisec;

	trc.min = MIN_OFFSET;
	trc.max = INFINITY;
	trc.d = refl_r(trc.d, n);
	cisec = NULL;
	refl_col = trace(lst, trc, depth, cisec);
	return (refl_col);
}

void		refr_init(t_trc *trc, t_vec3 *ctk, t_vec3 *eta, t_vec3 *n)
{
	trc->d = div_vec3f(trc->d, len_vec3(trc->d));
	ctk->x = -clampf(dot(trc->d, *n), -1.0, 1.0);
	eta->y = 1.0;
	if (ctk->x < 0)
	{
		ctk->x = -ctk->x;
		ctk->y = eta->y;
		eta->y = eta->z;
		eta->z = ctk->y;
		*n = invert_vec3(*n);
	}
	eta->x = eta->y / eta->z;
	ctk->z = 1 - eta->x * eta->x * (1 - ctk->x * ctk->x);
}

SDL_Color	get_refr_col(t_lst *lst, t_trc trc, t_vec3 n, float ito)
{
	SDL_Color	refr_col;
	t_vec3		ctk;
	t_vec3		eta;
	t_isec		*cisec;

	eta.z = ito;
	refr_init(&trc, &ctk, &eta, &n);
	if (ctk.z < 0)
		trc.d = cre_vec3(1, 0, 0);
	else
		trc.d = plus_vec3(mult_vec3f(trc.d, eta.x),
			mult_vec3f(n, (eta.x * ctk.x - sqrtf(ctk.z))));
	trc.d = div_vec3f(trc.d, len_vec3(trc.d));
	trc.d = invert_vec3(trc.d);
	trc.min = MIN_OFFSET;
	trc.max = INFINITY;
	lst->depth_refr -= 1;
	cisec = NULL;
	refr_col = trace(lst, trc, 0, cisec);
	return (refr_col);
}
