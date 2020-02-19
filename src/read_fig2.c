/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fig2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:43:40 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:40:15 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_mat_fig0(t_lst *lst, t_mat *mat, char mat_name[18], int *flag)
{
	while (mat)
	{
		if (ft_strcmp(mat_name, mat->name) == 0)
		{
			lst->scn->cur_fig->mat = mat;
			*flag = 1;
			break ;
		}
		mat = mat->next;
	}
}

int		set_mat_fig(t_lst *lst, char *word)
{
	char	**name;
	t_mat	*mat;
	char	mat_name[18];
	int		flag;

	if (!word || !(*word))
		return (0);
	if (!(name = ft_strsplit(word, ' ')) || !(name[0]))
	{
		lst->scn->cur_fig->mat = lst->scn->mats;
		return (free_words(name, 1));
	}
	ft_strncpy(mat_name, name[0], 18);
	mat = lst->scn->mats;
	flag = 0;
	set_mat_fig0(lst, mat, mat_name, &flag);
	if (!flag)
		lst->scn->cur_fig->mat = lst->scn->mats;
	return (free_words(name, 1));
}

int		set_rad_fig(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->cur_fig->rad = ft_atof(word);
	return (1);
}

int		set_ang_fig(t_lst *lst, char *word)
{
	t_fig	*fig;

	if (!word)
		return (0);
	fig = lst->scn->cur_fig;
	fig->ang = 0;
	if (fig->rad)
		return (1);
	fig->ang = ft_atof(word);
	if (fig->ang > -90 && fig->ang < 90)
	{
		fig->rad = tan(fig->ang * M_PI / 180);
		fig->rad = fig->rad * fig->rad + 1.0f;
	}
	else
		fig->rad = 33;
	return (1);
}

int		set_lim_fig(t_lst *lst, char *word)
{
	char	**limit;
	t_fig	*fig;

	if (!word)
		return (0);
	fig = lst->scn->cur_fig;
	if (!(limit = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (limit[0] && limit[1])
	{
		fig->limit.x = ft_atof(limit[0]);
		fig->limit.y = ft_atof(limit[1]);
		fig->limit.z = 0;
		return (free_words(limit, 1));
	}
	return (free_words(limit, 0));
}
