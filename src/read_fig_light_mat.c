/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fig_light_mat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:29:16 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 00:38:48 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_rot_fig(t_lst *lst, char *word)
{
	char	**coord;
	t_fig	*fig;

	if (!word)
		return (0);
	fig = lst->scn->cur_fig;
	if (!(coord = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (coord[0] && coord[1] && coord[2])
	{
		fig->alpha.x = ft_atof(coord[0]);
		fig->alpha.y = ft_atof(coord[1]);
		fig->alpha.z = ft_atof(coord[2]);
		set_m4_rx(&fig->mat_x, fig->alpha.x);
		set_m4_ry(&fig->mat_y, fig->alpha.y);
		set_m4_rz(&fig->mat_z, fig->alpha.z);
		rotation_fig(fig);
		return (free_words(coord, 1));
	}
	return (free_words(coord, 0));
}

int		set_col_lght(t_lst *lst, char *word)
{
	char	**col;
	t_lght	*lght;

	if (!word)
		return (0);
	lght = lst->scn->cur_lght;
	if (!(col = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (col[0] && col[1] && col[2])
	{
		lght->col.r = clamp(ft_atoi(col[0]), 0, 255);
		lght->col.g = clamp(ft_atoi(col[1]), 0, 255);
		lght->col.b = clamp(ft_atoi(col[2]), 0, 255);
		return (free_words(col, 1));
	}
	return (free_words(col, 0));
}

int		set_ints_lght(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->cur_lght->ints = ft_atof(word);
	return (1);
}

void	cre_mat0(t_lst *lst, t_mat **cur_mat, t_mat **mat)
{
	*cur_mat = lst->scn->mats;
	while ((*cur_mat)->next)
		*cur_mat = (*cur_mat)->next;
	(*cur_mat)->next = *mat;
}

int		cre_mat(t_lst *lst)
{
	t_mat	*mat;
	t_mat	*cur_mat;

	if (!(mat = (t_mat*)ft_memalloc(sizeof(t_mat))))
		return (0);
	mat->next = NULL;
	if (!lst->scn->mats)
	{
		ft_strcpy(mat->name, "default");
		mat->col = set_col(128, 128, 128, 255);
		load_map(&(mat->diff_map), 0);
		load_map(&(mat->norm_map), 0);
		load_map(&(mat->mask_map), 0);
		mat->refl = 0;
		mat->refr = 1;
		mat->spec = 1000;
		mat->transpare = 0;
		lst->scn->mats = mat;
	}
	else
		cre_mat0(lst, &cur_mat, &mat);
	lst->scn->cur_mat = mat;
	return (1);
}
