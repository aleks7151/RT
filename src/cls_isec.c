/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cls_isec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:56:11 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/10 21:56:39 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		add_link(t_isec *prev, t_isec *ins)
{
	prev->next = ins;
	ins->prev = prev;
}

void		add_intersection0(t_isec **cur, t_isec **isec, t_isec **prev)
{
	while (*cur)
	{
		if ((*isec)->t < (*cur)->t)
		{
			add_link(*prev, *isec);
			add_link(*isec, *cur);
			return ;
		}
		*prev = *cur;
		*cur = (*cur)->next;
	}
}

void		add_intersection(t_isec **cisec, t_isec *isec)
{
	t_isec *cur;
	t_isec *prev;

	if ((*cisec)->fig == NULL)
	{
		free((*cisec));
		*cisec = isec;
		return ;
	}
	cur = *cisec;
	prev = NULL;
	if (!cur || isec->t < cur->t)
	{
		*cisec = isec;
		if (cur != NULL)
		{
			add_link(isec, cur);
		}
		return ;
	}
	add_intersection0(&cur, &isec, &prev);
	add_link(prev, isec);
}

void		cls_isec0(t_hit *hit, t_fig **cur_fig, t_trc trc, t_isec **cisec)
{
	if (hit->count == 2)
	{
		if (hit->isec2->t >= trc.min && hit->isec2->t <= trc.max)
		{
			hit->isec2->prev = NULL;
			hit->isec2->next = NULL;
			add_intersection(cisec, hit->isec2);
		}
		else
			free(hit->isec2);
	}
	*cur_fig = (*cur_fig)->next;
}

void		cls_isec(t_isec **cisec, t_lst *lst, t_trc trc)
{
	t_fig	*cur_fig;
	t_hit	hit;

	(*cisec)->t = INFINITY;
	(*cisec)->uv.x = INFINITY;
	(*cisec)->uv.y = INFINITY;
	(*cisec)->fig = NULL;
	(*cisec)->n = cre_vec3(0, 0, 1);
	cur_fig = lst->scn->figs;
	while (cur_fig)
	{
		sel_fig_check(lst, &hit, trc, cur_fig);
		if (hit.count == 1 || hit.count == 2)
		{
			if (hit.isec1->t >= trc.min && hit.isec1->t <= trc.max)
			{
				hit.isec1->prev = NULL;
				hit.isec1->next = NULL;
				add_intersection(cisec, hit.isec1);
			}
			else
				free(hit.isec1);
		}
		cls_isec0(&hit, &cur_fig, trc, cisec);
	}
}
