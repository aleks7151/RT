/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:30:34 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:42:15 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_diff_map_scn(t_lst *lst, char *word)
{
	char **filename;

	if (!word || !(*word))
		return (0);
	if (!(filename = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	load_map(&(lst->scn->diff_map), filename[0]);
	return (free_words(filename, 1));
}

int		set_fog_enable(t_lst *lst, char *word)
{
	float e;

	if (!word)
		return (0);
	e = ft_atof(word);
	if (e != 1)
		e = 0;
	lst->scn->fog.enable = e;
	return (1);
}

int		set_fog_near(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->fog.near = ft_atof(word);
	return (1);
}

int		set_fog_max_tr(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->fog.max_tr = clampf(1 - ft_atof(word), 0, 1);
	return (1);
}

int		set_fog_color(t_lst *lst, char *word)
{
	char	**col;
	t_fog	*fog;

	if (!word)
		return (0);
	fog = &lst->scn->fog;
	if (!(col = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (col[0] && col[1] && col[2])
	{
		fog->col.r = clamp(ft_atoi(col[0]), 0, 255);
		fog->col.g = clamp(ft_atoi(col[1]), 0, 255);
		fog->col.b = clamp(ft_atoi(col[2]), 0, 255);
		return (free_words(col, 1));
	}
	return (free_words(col, 0));
}
