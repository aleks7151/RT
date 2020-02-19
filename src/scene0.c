/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:57:54 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/09 17:57:55 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_tag0(char **word, const char *tag[TAGS], t_tag *ctag, t_lst *l)
{
	if (ft_strcmp(word[0], tag[ctag->cur_tag]) == 0)
	{
		if (!(cre_cur_obj(l, ctag)))
			return (0);
		ctag->read_tag = ctag->cur_tag;
		ctag->count = 0;
		return (1);
	}
	ctag->cur_tag += 1;
	return (2);
}

int		check_tag(t_lst *l, char **word, t_tag *ctag)
{
	const char	*tag[TAGS];
	int			res;
	int			fun;

	tag[0] = "[scene]";
	tag[1] = "[material]";
	tag[2] = "[figure]";
	tag[3] = "[light]";
	res = 0;
	ctag->cur_tag = SCENE;
	while (ctag->cur_tag < TAGS)
		if ((fun = check_tag0(word, tag, ctag, l)) != 2)
			return (fun);
	if (!check_valid_iter(ctag))
		return (0);
	if (ctag->read_tag == SCENE)
		res = l->set->f_scn[ctag->count](l, word[1]);
	else if (ctag->read_tag == MATERIAL)
		res = l->set->f_mat[ctag->count](l, word[1]);
	else if (ctag->read_tag == FIGURE)
		res = l->set->f_fig[ctag->count](l, word[1]);
	else if (ctag->read_tag == LIGHT)
		res = l->set->f_lght[ctag->count](l, word[1]);
	ctag->count += 1;
	return (res);
}
