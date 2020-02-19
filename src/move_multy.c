/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_multy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:03:57 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/14 17:42:52 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move_light(t_lst *lst, SDL_Point p)
{
	t_lght	*lght;
	t_vec3	c_p;
	t_vec3	c_p0;

	c_p = set_vec3(lst->scn->cam_pos);
	c_p0 = set_vec3(lst->scn->cam_pos0);
	mult_m3(&c_p0, c_p0, lst->camera_z);
	mult_m3(&c_p0, c_p0, lst->camera_x);
	mult_m3(&c_p0, c_p0, lst->camera_y);
	c_p = plus_vec3(c_p, c_p0);
	lght = lst->scn->cur_lght;
	lght->begin_pos.x = ((float)p.x - H_W) / H_W *
		((lght->begin_pos.z - lst->scn->cam_pos.z) / 2) + lst->scn->cam_pos.x;
	lght->begin_pos.y = -((float)p.y - H_H) / H_H *
		((lght->begin_pos.z - lst->scn->cam_pos.z) / 2) + lst->scn->cam_pos.y;
	lght->begin_pos.x *= RATIO;
	lght->pos = set_vec3(lght->begin_pos);
	lght->pos = minus_vec3(lght->pos, lst->scn->cam_pos);
	mult_m3(&lght->pos, lght->pos, lst->camera_z);
	mult_m3(&lght->pos, lght->pos, lst->camera_x);
	mult_m3(&lght->pos, lght->pos, lst->camera_y);
	lght->pos = plus_vec3(lght->pos, lst->scn->cam_pos);
}

void	move_fig(t_lst *lst, SDL_Point p)
{
	t_fig	*fig;
	t_vec3	c_p;
	t_vec3	c_p0;

	c_p = set_vec3(lst->scn->cam_pos);
	c_p0 = set_vec3(lst->scn->cam_pos0);
	mult_m3(&c_p0, c_p0, lst->camera_z);
	mult_m3(&c_p0, c_p0, lst->camera_x);
	mult_m3(&c_p0, c_p0, lst->camera_y);
	c_p = plus_vec3(c_p, c_p0);
	fig = lst->scn->cur_fig;
	fig->begin_pos.x = ((float)p.x - H_W) / H_W *
		((fig->begin_pos.z - c_p.z) / 2) + c_p.x;
	fig->begin_pos.y = -((float)p.y - H_H) / H_H *
		((fig->begin_pos.z - c_p.z) / 2) + c_p.y;
	fig->begin_pos.x *= RATIO;
	fig->pos = set_vec3(fig->begin_pos);
	fig->pos = minus_vec3(fig->pos, c_p);
	mult_m3(&fig->pos, fig->pos, lst->camera_z);
	mult_m3(&fig->pos, fig->pos, lst->camera_x);
	mult_m3(&fig->pos, fig->pos, lst->camera_y);
	fig->pos = plus_vec3(fig->pos, c_p);
}

void	multy_x(t_lst *lst, int tmp)
{
	lst->scn->cur_fig->alpha.x += tmp;
	set_m4_rx(&lst->scn->cur_fig->mat_x, lst->scn->cur_fig->alpha.x);
	rotation_fig(lst->scn->cur_fig);
}

void	multy_y(t_lst *lst, int tmp)
{
	lst->scn->cur_fig->alpha.y += tmp;
	set_m4_ry(&lst->scn->cur_fig->mat_y, lst->scn->cur_fig->alpha.y);
	rotation_fig(lst->scn->cur_fig);
}

void	multy_z(t_lst *lst, int tmp)
{
	lst->scn->cur_fig->alpha.z += tmp;
	set_m4_rz(&lst->scn->cur_fig->mat_z, lst->scn->cur_fig->alpha.z);
	rotation_fig(lst->scn->cur_fig);
}
