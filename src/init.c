/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:37:19 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 23:59:42 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_f_read0(t_lst *lst)
{
	lst->set->cre_lght = cre_lght;
	lst->set->f_lght[0] = set_type_lght;
	lst->set->f_lght[1] = set_pos_lght;
	lst->set->f_lght[2] = set_dir_lght;
	lst->set->f_lght[3] = set_angle_lght;
	lst->set->f_lght[4] = set_ints_lght;
	lst->set->f_lght[5] = set_col_lght;
	lst->set->cre_mat = cre_mat;
	lst->set->f_mat[0] = set_name_mat;
	lst->set->f_mat[1] = set_col_mat;
	lst->set->f_mat[2] = set_diff_map_mat;
	lst->set->f_mat[3] = set_norm_map_mat;
	lst->set->f_mat[4] = set_mask_map_mat;
	lst->set->f_mat[5] = set_spec_mat;
	lst->set->f_mat[6] = set_refl_mat;
	lst->set->f_mat[7] = set_refr_mat;
	lst->set->f_mat[8] = set_transpare_mat;
}

void	init_f_read(t_lst *lst)
{
	lst->set->f_scn[0] = set_pos_cam;
	lst->set->f_scn[1] = set_rot_cam;
	lst->set->f_scn[2] = set_cam_focus_dist;
	lst->set->f_scn[3] = set_col_bgc;
	lst->set->f_scn[4] = set_diff_map_scn;
	lst->set->f_scn[5] = set_fog_enable;
	lst->set->f_scn[6] = set_fog_near;
	lst->set->f_scn[7] = set_fog_max_tr;
	lst->set->f_scn[8] = set_fog_color;
	lst->set->f_scn[9] = set_inv_surf;
	lst->set->cre_fig = cre_fig;
	lst->set->f_fig[0] = set_type_fig;
	lst->set->f_fig[1] = set_pos_fig;
	lst->set->f_fig[2] = set_dir_fig;
	lst->set->f_fig[3] = set_rot_fig;
	lst->set->f_fig[4] = set_rad_fig;
	lst->set->f_fig[5] = set_ang_fig;
	lst->set->f_fig[6] = set_lim_fig;
	lst->set->f_fig[7] = set_mat_fig;
	lst->set->f_fig[8] = set_uv_scale;
	lst->set->f_fig[9] = set_uv_rot;
	lst->set->f_fig[10] = set_uv_move;
	init_f_read0(lst);
}

int		init_sdl0(t_lst *lst)
{
	set_rect(&lst->mrect, 10, 10);
	lst->mrect.w = S_W;
	lst->mrect.h = H_W;
	lst->shd = 3;
	lst->show_menu = 1;
	lst->show_help = 1;
	return (1);
}

int		init_sdl(t_lst *lst)
{
	int *data;
	int h;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (0);
	if (TTF_Init() == -1)
		return (0);
	lst->win = 0;
	lst->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, S_W, S_H, SDL_WINDOW_SHOWN);
	if (!lst->win)
		return (0);
	lst->img = SDL_GetWindowSurface(lst->win);
	if (!lst->img)
		return (0);
	lst->data = (int *)lst->img->pixels;
	if (!(lst->mimg = SDL_CreateRGBSurface(0, S_W, S_H, 32,
		0xff0000, 0x00ff00, 0x0000ff, 0xff000000)))
		return (0);
	data = (int *)lst->mimg->pixels;
	h = -1;
	while (++h < S_W / 5 * S_H)
		data[h] = 0x77ff0000;
	return (init_sdl0(lst));
}

int		scene_init(t_lst *lst, char *file)
{
	if (!(lst->set = (t_read*)ft_memalloc(sizeof(t_read))))
		return (0);
	init_f_read(lst);
	if (!(lst->scn = (t_scn*)ft_memalloc(sizeof(t_scn))))
		return (0);
	lst->scn->cur_fig = NULL;
	lst->scn->cur_lght = NULL;
	lst->scn->mats = NULL;
	lst->scn->figs = NULL;
	lst->scn->lghts = NULL;
	lst->scn->shadow = 1;
	lst->mouse_light = 0;
	lst->change = 0;
	lst->scn->cam_pos0.x = 0;
	lst->scn->cam_pos0.y = 0;
	lst->scn->cam_pos0.z = 0;
	lst->post_effects = 0;
	if (!(lst->data_dop = ft_memalloc(sizeof(int) * (S_H * S_W))))
		return (0);
	lst->num_file_for_screen = 0;
	if (!(read_scene(lst, file)))
		return (0);
	if (!lst->scn->cur_fig || !lst->scn->cur_lght)
		return (0);
	return (1);
}
