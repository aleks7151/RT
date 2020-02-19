/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scn0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:39:22 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 00:42:40 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_pos_cam(t_lst *lst, char *word)
{
	char	**coord;

	if (!word)
		return (0);
	if (!(coord = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (coord[0] && coord[1] && coord[2])
	{
		lst->scn->cam_pos.x = ft_atof(coord[0]);
		lst->scn->cam_pos.y = ft_atof(coord[1]);
		lst->scn->cam_pos.z = ft_atof(coord[2]);
		return (free_words(coord, 1));
	}
	return (free_words(coord, 0));
}

int		set_rot_cam(t_lst *lst, char *word)
{
	char	**coord;

	if (!word)
		return (0);
	if (!(coord = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (coord[0] && coord[1] && coord[2])
	{
		lst->alpha_cam.x = ft_atof(coord[0]);
		lst->alpha_cam.y = ft_atof(coord[1]);
		lst->alpha_cam.z = ft_atof(coord[2]);
		set_m4_rx(&lst->camera_x, lst->alpha_cam.x);
		set_m4_ry(&lst->camera_y, lst->alpha_cam.y);
		set_m4_rz(&lst->camera_z, lst->alpha_cam.z);
		return (free_words(coord, 1));
	}
	return (free_words(coord, 0));
}

int		set_cam_focus_dist(t_lst *lst, char *word)
{
	if (!word)
		return (0);
	lst->scn->cam_focus_dist = ft_atof(word);
	return (1);
}

int		set_col_bgc(t_lst *lst, char *word)
{
	char		**col;

	if (!word)
		return (0);
	if (!(col = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	if (col[0] && col[1] && col[2])
	{
		lst->scn->bgc.r = clamp(ft_atoi(col[0]), 0, 255);
		lst->scn->bgc.g = clamp(ft_atoi(col[1]), 0, 255);
		lst->scn->bgc.b = clamp(ft_atoi(col[2]), 0, 255);
		return (free_words(col, 1));
	}
	return (free_words(col, 0));
}

int		set_inv_surf(t_lst *lst, char *word)
{
	float	e;
	int		inv;

	inv = 1;
	if (!word)
		return (0);
	e = ft_atof(word);
	if (e != 1)
		inv = 0;
	lst->scn->inv_surf = inv;
	return (1);
}
