/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shadow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 00:33:15 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 00:35:54 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** calculate vector of reflection
*/

t_vec3		get_shadow0(t_lst *lst, t_isec *shdw, t_vec3 b_col)
{
	t_vec3	s;

	if (lst->scn->shadow && shdw->fig != NULL)
	{
		s = transpare_shadow(shdw, b_col);
		free_isec_list(shdw);
		return (s);
	}
	else if (shdw->fig != NULL)
		free_isec_list(shdw);
	else
		free(shdw);
	return (b_col);
}

t_vec3		get_shadow(t_lst *lst, t_trc *trc, t_l_prm b, t_lght *c_lght)
{
	t_isec	*shdw;
	t_vec3	b_col;

	b_col = cre_vec3(c_lght->col.r * c_lght->ints / 255.0, c_lght->col.g
		* c_lght->ints / 255.0, c_lght->col.b * c_lght->ints / 255.0);
	if (c_lght->type == point || c_lght->type == lconus)
		trc_init(trc, c_lght, b);
	else if (c_lght->type == direct)
	{
		trc->d.x = c_lght->dir.x;
		trc->d.y = c_lght->dir.y;
		trc->d.z = c_lght->dir.z;
		trc->max = INFINITY;
	}
	if (!(shdw = malloc(sizeof(t_isec))))
		ft_exit("Not malloc");
	cls_isec(&shdw, lst, *trc);
	return (get_shadow0(lst, shdw, b_col));
}
