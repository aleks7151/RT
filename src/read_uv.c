/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_uv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:51:20 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 15:36:25 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_uv_scale(t_lst *lst, char *word)
{
	char	**scale;
	t_fig	*fig;

	if (!word)
		return (0);
	fig = lst->scn->cur_fig;
	if (!(scale = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (scale[0] && scale[1])
	{
		fig->uvt.scale.x = 1.0 / ft_atof(scale[0]);
		fig->uvt.scale.y = 1.0 / ft_atof(scale[1]);
		fig->uvt.scale.z = 0;
		return (free_words(scale, 1));
	}
	return (free_words(scale, 0));
}

int		set_uv_rot(t_lst *lst, char *word)
{
	float alpha;

	if (!word)
		return (0);
	alpha = ft_atof(word);
	lst->scn->cur_fig->uvt.rot = alpha;
	while (alpha >= 180)
		alpha -= 360;
	while (alpha < -180)
		alpha += 360;
	alpha = alpha * M_PI / 180.0;
	lst->scn->cur_fig->uvt.rot_tr.x = cos(alpha);
	lst->scn->cur_fig->uvt.rot_tr.y = sin(alpha);
	return (1);
}

int		set_uv_move(t_lst *lst, char *word)
{
	char	**move;
	t_fig	*fig;

	if (!word)
		return (0);
	fig = lst->scn->cur_fig;
	if (!(move = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (move[0] && move[1])
	{
		fig->uvt.move.x = ft_atof(move[0]);
		fig->uvt.move.y = ft_atof(move[1]);
		fig->uvt.move.z = 0;
		return (free_words(move, 1));
	}
	return (free_words(move, 0));
}
