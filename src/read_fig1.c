/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fig1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:43:40 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:39:46 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		cre_fig(t_lst *lst)
{
	t_fig	*fig;
	t_fig	*cur_fig;

	if (!(fig = (t_fig*)malloc(sizeof(t_fig))))
		return (0);
	fig->next = NULL;
	fig->mat = lst->scn->mats;
	if (!lst->scn->figs)
		lst->scn->figs = fig;
	else
	{
		cur_fig = lst->scn->figs;
		while (cur_fig->next)
			cur_fig = cur_fig->next;
		cur_fig->next = fig;
	}
	lst->scn->cur_fig = fig;
	return (1);
}

int		set_type_fig(t_lst *lst, char *word)
{
	const char	f_type[MAX_FIGS][10] =
	{"sphere", "cylinder", "plane", "conus", "inv_sph"};
	int			i;
	int			type;

	i = -1;
	type = -1;
	while (++i < MAX_FIGS)
	{
		if (ft_strcmp(word, f_type[i]) == 0)
		{
			type = i;
			break ;
		}
	}
	if (type < 0)
		return (0);
	lst->scn->cur_fig->type = type;
	return (1);
}

int		set_pos_fig(t_lst *lst, char *word)
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
		fig->begin_pos.x = ft_atof(coord[0]);
		fig->begin_pos.y = ft_atof(coord[1]);
		fig->begin_pos.z = ft_atof(coord[2]);
		fig->pos.x = fig->begin_pos.x;
		fig->pos.y = fig->begin_pos.y;
		fig->pos.z = fig->begin_pos.z;
		return (free_words(coord, 1));
	}
	return (free_words(coord, 0));
}

int		set_dir_fig(t_lst *lst, char *word)
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
		fig->begin.x = ft_atof(coord[0]);
		fig->begin.y = ft_atof(coord[1]);
		fig->begin.z = ft_atof(coord[2]);
		return (free_words(coord, 1));
	}
	return (free_words(coord, 0));
}

void	rotation_fig(t_fig *fig)
{
	t_vec3	tmp;

	mult_m3(&fig->dir, cre_vec3(0, 1.0, 0), fig->mat_z);
	mult_m3(&fig->dir, fig->dir, fig->mat_x);
	mult_m3(&fig->dir, fig->dir, fig->mat_y);
	fig->dir = div_vec3f(fig->dir, len_vec3(fig->dir));
	mult_m3(&fig->look, cre_vec3(0, 0, 1.0), fig->mat_z);
	mult_m3(&fig->look, fig->look, fig->mat_x);
	mult_m3(&fig->look, fig->look, fig->mat_y);
	fig->look = div_vec3f(fig->look, len_vec3(fig->look));
	mult_m3(&fig->right, cre_vec3(1.0, 0, 0), fig->mat_z);
	mult_m3(&fig->right, fig->right, fig->mat_x);
	mult_m3(&fig->right, fig->right, fig->mat_y);
	fig->right = div_vec3f(fig->right, len_vec3(fig->right));
	mult_m3(&tmp, fig->begin, fig->mat_z);
	mult_m3(&tmp, tmp, fig->mat_x);
	mult_m3(&tmp, tmp, fig->mat_y);
	fig->pos = plus_vec3(minus_vec3(fig->begin_pos, fig->begin), tmp);
}
