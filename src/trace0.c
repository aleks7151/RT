/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:05:40 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/12 21:48:09 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_refr(t_lst *lst, t_trc *trc,
	t_isec *ci, SDL_Color *tres)
{
	float transp;

	if (ci->fig->mat->refr > 1)
	{
		if (ci->fig->mat->mask_map.map &&
			ci->uv.x && ci->uv.x != INFINITY)
			transp = get_transp_from_file(ci->fig->mat->mask_map,
				ci->uv);
		else
			transp = ci->fig->mat->transpare;
		trc->o = set_vec3(trc->p);
		*tres = mix_color(get_refr_col(lst, *trc, ci->n2, ci->fig->mat->refr),
			*tres, 1 - transp);
	}
}

int			init_trace(t_lst *lst, t_isec **cisec, t_trc trc, SDL_Color *col)
{
	if (!(*cisec = ft_memalloc(sizeof(t_isec))))
		ft_exit("failed to alloc cisec");
	cls_isec(cisec, lst, trc);
	*col = return_background(lst, trc);
	if ((*cisec)->fig == NULL)
	{
		free(*cisec);
		return (1);
	}
	return (0);
}

int			idono(t_vec3 *fkt, SDL_Color *res,
	SDL_Color tres, t_isec **cur_isec)
{
	if (fkt->z < 1.0)
	{
		fkt->y = (1.0 - fkt->z) * fkt->x;
		*res = plus_sdl_color(*res, mult_sdl_color(tres, fkt->y));
		fkt->x -= fkt->y;
	}
	if ((fkt->x < 0.05) || fkt->z == 0.0)
		return (1);
	*cur_isec = (*cur_isec)->next;
	return (0);
}

void		init_trace0(t_lst *lst, int depth, t_vec3 *fkt, SDL_Color *res)
{
	fkt->x = 1.0f;
	*res = (SDL_Color){0, 0, 0, 255};
	lst->depth = depth;
}

SDL_Color	return_trace(t_lst *lst, t_vec3 fkt, SDL_Color col, t_isec **cisec)
{
	if (lst->shd < TRASPARENT)
		lst->res_help = plus_sdl_color(lst->res_help, col);
	else
	{
		if (fkt.x > 0)
			lst->res_help = plus_sdl_color(lst->res_help,
				mult_sdl_color(col, fkt.x));
		if (lst->shd && lst->scn->fog.enable)
			lst->res_help = mix_color(lst->scn->fog.col,
				lst->res_help, (*cisec)->t / lst->scn->fog.near);
	}
	free_isec_list(*cisec);
	return (lst->res_help);
}
