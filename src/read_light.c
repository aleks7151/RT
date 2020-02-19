/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:44:55 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 00:40:39 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		cre_lght(t_lst *lst)
{
	t_lght	*lght;
	t_lght	*cur_lght;

	if (!(lght = (t_lght*)malloc(sizeof(t_lght))))
		return (0);
	lght->next = NULL;
	if (!lst->scn->lghts)
		lst->scn->lghts = lght;
	else
	{
		cur_lght = lst->scn->lghts;
		while (cur_lght->next)
			cur_lght = cur_lght->next;
		cur_lght->next = lght;
	}
	lst->scn->cur_lght = lght;
	return (1);
}

int		set_type_lght(t_lst *lst, char *word)
{
	const char	l_type[MAX_LGHT][8] = {"ambient", "point", "direct", "lconus"};
	int			i;
	int			type;

	i = -1;
	type = -1;
	while (++i < MAX_LGHT)
	{
		if (ft_strcmp(word, l_type[i]) == 0)
		{
			type = i;
			break ;
		}
	}
	if (type < 0)
		return (0);
	lst->scn->cur_lght->type = type;
	return (1);
}

int		set_pos_lght(t_lst *lst, char *word)
{
	char	**coord;
	t_lght	*lght;

	if (!word)
		return (0);
	lght = lst->scn->cur_lght;
	if (!word)
		return (0);
	if (!(coord = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (coord[0] && coord[1] && coord[2])
	{
		lght->begin_pos.x = ft_atof(coord[0]);
		lght->begin_pos.y = ft_atof(coord[1]);
		lght->begin_pos.z = ft_atof(coord[2]);
		lght->pos.x = lght->begin_pos.x;
		lght->pos.y = lght->begin_pos.y;
		lght->pos.z = lght->begin_pos.z;
		return (free_words(coord, 1));
	}
	return (free_words(coord, 0));
}

int		set_dir_lght(t_lst *lst, char *word)
{
	char	**coord;
	t_lght	*lght;

	if (!word)
		return (0);
	lght = lst->scn->cur_lght;
	if (!(coord = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (coord[0] && coord[1] && coord[2])
	{
		lght->dir.x = ft_atof(coord[0]);
		lght->dir.y = ft_atof(coord[1]);
		lght->dir.z = ft_atof(coord[2]);
		if (len_vec3(lght->dir) != 0)
			lght->dir = div_vec3f(lght->dir, len_vec3(lght->dir));
		return (free_words(coord, 1));
	}
	return (free_words(coord, 0));
}

int		set_angle_lght(t_lst *lst, char *word)
{
	float angle;

	if (!word)
		return (0);
	angle = ft_atof(word);
	if (angle < 0)
		angle = -angle;
	lst->scn->cur_lght->angle = angle;
	return (1);
}
