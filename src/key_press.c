/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:07:39 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/18 21:02:55 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cycle(t_lst *lst)
{
	while (lst->scn->cur_lght)
	{
		lst->scn->cur_lght = lst->scn->cur_lght->next;
		if (lst->scn->cur_lght && (lst->scn->cur_lght->type == point ||
			lst->scn->cur_lght->type == lconus))
			break ;
	}
	if (!lst->scn->cur_lght)
	{
		lst->scn->cur_lght = lst->scn->lghts;
		while (lst->scn->cur_lght)
		{
			if (lst->scn->cur_lght->type == point)
				break ;
			lst->scn->cur_lght = lst->scn->cur_lght->next;
		}
	}
}

int		mouse_light(t_lst *lst)
{
	if (!lst->mouse_light)
	{
		lst->scn->cur_lght = lst->scn->lghts;
		while (lst->scn->cur_lght)
		{
			if (lst->scn->cur_lght->type == point)
				break ;
			lst->scn->cur_lght = lst->scn->cur_lght->next;
		}
		if (!lst->scn->cur_lght)
			return (0);
		lst->mouse_light = 1;
	}
	else
		cycle(lst);
	return (1);
}

int		key_press1(SDL_Keycode key, t_lst *lst)
{
	if (key == SDLK_f)
	{
		if (lst->mouse_light)
			lst->mouse_light = 0;
		else if (lst->scn->cur_fig && lst->scn->cur_fig->next)
			lst->scn->cur_fig = lst->scn->cur_fig->next;
		else
			lst->scn->cur_fig = lst->scn->figs;
		return (0);
	}
	else if (key == SDLK_SPACE)
		lst->scn->shadow = (lst->scn->shadow) ? 0 : 1;
	else if (key == SDLK_F5)
		lst->shd = (lst->shd == REFRACT) ? SIMPLE : lst->shd + 1;
	else if (key == SDLK_l)
		multy_y(lst, 3);
	else if (key == SDLK_y)
		multy_z(lst, -3);
	else if (key == SDLK_t)
		multy_z(lst, 3);
	else if (key == SDLK_g && !mouse_light(lst))
		return (0);
	if (lst->shd == 1)
		lst->shd = 2;
	return (1);
}

int		key_press0(SDL_Keycode key, t_lst *lst)
{
	if (key == SDLK_w || key == SDLK_s)
	{
		lst->alpha_cam.x += 3;
		if (key == SDLK_w)
			lst->alpha_cam.x -= 6;
		ret(lst);
		set_m4_rx(&lst->camera_x, lst->alpha_cam.x);
	}
	else if (key == SDLK_a || key == SDLK_d)
	{
		lst->alpha_cam.y -= 3;
		if (key == SDLK_d)
			lst->alpha_cam.y += 6;
		ret(lst);
		set_m4_ry(&lst->camera_y, lst->alpha_cam.y);
	}
	else if (key == SDLK_q || key == SDLK_e)
	{
		lst->alpha_cam.z -= 3;
		if (key == SDLK_q)
			lst->alpha_cam.z += 6;
		ret(lst);
		set_m4_rz(&lst->camera_z, lst->alpha_cam.z);
	}
	return (key_press1(key, lst));
}

int		key_press(SDL_Keycode key, t_lst *lst)
{
	if (key == 8)
		return (save_scene(lst));
	else if (key == 13)
		return (scrin(lst));
	else if (key == 91)
	{
		lst->post_effects -= 1;
		if (lst->post_effects < 0)
			lst->post_effects = END_FOR_POST_EFFECTS;
		return (0);
	}
	else if (key == 93)
	{
		lst->post_effects += 1;
		if (lst->post_effects > END_FOR_POST_EFFECTS)
			lst->post_effects = 0;
		return (0);
	}
	else if (key == SDLK_F6)
		lst->show_menu = (lst->show_menu == 1) ? 0 : 1;
	else if (key == SDLK_x)
		lst->show_help = (lst->show_help == 1) ? 0 : 1;
	return (key_press_dop(key, lst));
}
