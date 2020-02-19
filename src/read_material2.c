/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_material2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:33:16 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 00:41:34 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_col_mat(t_lst *lst, char *word)
{
	char	**col;
	t_mat	*mat;

	if (!word)
		return (0);
	mat = lst->scn->cur_mat;
	if (!(col = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (col[0] && col[1] && col[2])
	{
		mat->col.r = clamp(ft_atoi(col[0]), 0, 255);
		mat->col.g = clamp(ft_atoi(col[1]), 0, 255);
		mat->col.b = clamp(ft_atoi(col[2]), 0, 255);
		return (free_words(col, 1));
	}
	return (free_words(col, 0));
}

int		set_spec_mat(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->cur_mat->spec = ft_atoi(word);
	return (1);
}

int		set_refl_mat(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->cur_mat->refl = ft_atof(word);
	return (1);
}

int		set_transpare_mat(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	if (lst->scn->cur_mat->mask_map.map != 0)
		lst->scn->cur_mat->transpare = 1;
	else
		lst->scn->cur_mat->transpare = ft_atof(word);
	return (1);
}

int		set_refr_mat(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->cur_mat->refr = ft_atof(word);
	return (1);
}
