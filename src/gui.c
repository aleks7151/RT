/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:22:21 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 00:27:36 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_figure0(t_lst *lst, t_fig *fig)
{
	fig->look = (t_vec3){0, 0, 1, 0};
	fig->right = (t_vec3){1, 0, 0, 0};
	fig->ang = 0;
	if (fig->type == conus)
		fig->ang = 30;
	if (fig->ang > -90 && fig->ang < 90)
	{
		fig->rad = tan(fig->ang * M_PI / 180);
		fig->rad = fig->rad * fig->rad + 1.0f;
	}
	else
		fig->rad = 33;
	fig->limit = (t_vec3){0, 0, 0, 0};
	fig->alpha = (t_vec3){0, 0, 0, 0};
	set_m4_rx(&fig->mat_x, fig->alpha.x);
	set_m4_ry(&fig->mat_y, fig->alpha.y);
	set_m4_rz(&fig->mat_z, fig->alpha.z);
	fig->uvt.scale = (t_vec3){1, 1, 0, 0};
	fig->uvt.move = (t_vec3){0, 0, 0, 0};
	fig->uvt.rot = 0;
	fig->uvt.rot_tr = (t_vec3){1, 0, 0, 0};
	fig->mat = lst->scn->cur_mat;
}

void	add_figure(t_lst *lst, int num_fig)
{
	t_fig *fig;

	fig = lst->scn->figs;
	while (fig->next)
		fig = fig->next;
	if (!(fig->next = malloc(sizeof(t_fig))))
		exit(0);
	fig = fig->next;
	fig->next = NULL;
	lst->scn->cur_fig = fig;
	if (num_fig == sphere)
		fig->type = sphere;
	else if (num_fig == cylinder)
		fig->type = cylinder;
	else if (num_fig == plane)
		fig->type = plane;
	else if (num_fig == conus)
		fig->type = conus;
	else if (num_fig == inv_sph)
		fig->type = inv_sph;
	fig->pos = (t_vec3){0, 0, 0, 0};
	fig->begin_pos = (t_vec3){0, 0, 0, 0};
	fig->dir = (t_vec3){0, 1, 0, 0};
	fig->begin = (t_vec3){0, 0, 0, 0};
	add_figure0(lst, fig);
}

void	next_mat(t_lst *lst)
{
	if (!lst->scn->cur_fig->mat->next)
		lst->scn->cur_fig->mat = lst->scn->mats;
	else
		lst->scn->cur_fig->mat = lst->scn->cur_fig->mat->next;
}

void	search_fig0(t_lst *lst, t_trc trc)
{
	t_isec		*cisec;

	mult_m3(&trc.d, trc.d, lst->camera_z);
	mult_m3(&trc.d, trc.d, lst->camera_x);
	mult_m3(&trc.d, trc.d, lst->camera_y);
	if (!(cisec = malloc(sizeof(t_isec))))
		ft_exit("Not malloc");
	cls_isec(&cisec, lst, trc);
	if (cisec->fig)
	{
		lst->scn->cur_fig = cisec->fig;
		free_isec_list(cisec);
	}
	else
		free(cisec);
}

void	search_fig(t_lst *lst, int x, int y)
{
	t_trc		trc;

	x -= H_W;
	y -= H_H;
	y *= -1;
	trc.min = 1.0f;
	trc.max = INFINITY;
	trc.o = set_vec3(lst->scn->cam_pos0);
	mult_m3(&trc.o, trc.o, lst->camera_z);
	mult_m3(&trc.o, trc.o, lst->camera_x);
	mult_m3(&trc.o, trc.o, lst->camera_y);
	trc.o = plus_vec3(trc.o, lst->scn->cam_pos);
	trc.d.x = (float)x * RATIO / H_W;
	trc.d.y = (float)y / H_H;
	trc.d.z = lst->scn->cam_focus_dist;
	search_fig0(lst, trc);
}
