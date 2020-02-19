/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:08:27 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/18 18:27:40 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		close_window(void *lst)
{
	(void)lst;
	exit(0);
}

void	mouse_move(SDL_MouseMotionEvent *e, t_lst *lst)
{
	lst->cursor.x = e->x;
	lst->cursor.y = e->y;
	if (!lst->change)
		return ;
	if (lst->mouse_light)
		move_light(lst, lst->cursor);
	else
		move_fig(lst, lst->cursor);
}

void	mouse_weel(Sint32 y, t_lst *lst)
{
	if (lst->mouse_light)
	{
		lst->scn->cur_lght->begin_pos.z -= 3;
		if (y < 0)
			lst->scn->cur_lght->begin_pos.z += 6;
		move_light(lst, lst->cursor);
	}
	else
	{
		lst->scn->cur_fig->begin_pos.z -= 3;
		if (y < 0)
			lst->scn->cur_fig->begin_pos.z += 6;
		move_fig(lst, lst->cursor);
	}
}

int		check_if(t_lst *lst, SDL_MouseButtonEvent *e, int n)
{
	if (lst->show_menu && !lst->mouse_light && e->button == SDL_BUTTON_LEFT)
	{
		if (n == 0 && e->x >= 10 + 5 && e->y >= 100 + 75
			&& e->x <= 10 + 80 && e->y <= 100 + 98)
			return (1);
		else if (n == 1 && e->x >= 10 + 5 && e->y >= 100 + 135
			&& e->x <= 10 + 80 && e->y <= 100 + 158)
			return (1);
		else if (n == 2 && e->x >= 10 + 90 && e->y >= 100 + 75
			&& e->x <= 10 + 165 && e->y <= 100 + 98)
			return (1);
		else if (n == 3 && e->x >= 10 + 5 && e->y >= 100 + 105
			&& e->x <= 10 + 80 && e->y <= 100 + 128)
			return (1);
		else if (n == 4 && e->x >= 10 + 90 && e->y >= 100 + 105
			&& e->x <= 10 + 165 && e->y <= 100 + 128)
			return (1);
		else if (n == 5 && e->x >= 10 + 90 && e->y >= 100 + 135
			&& e->x <= 10 + 165 && e->y <= 100 + 158)
			return (1);
	}
	return (0);
}

void	mouse_press(SDL_MouseButtonEvent *e, t_lst *lst)
{
	if (check_if(lst, e, 0))
		add_figure(lst, 0);
	else if (check_if(lst, e, 1))
		add_figure(lst, 1);
	else if (check_if(lst, e, 2))
		add_figure(lst, 2);
	else if (check_if(lst, e, 3))
		add_figure(lst, 3);
	else if (check_if(lst, e, 4))
		add_figure(lst, 4);
	else if (check_if(lst, e, 5))
		next_mat(lst);
	else if (e->button == SDL_BUTTON_RIGHT && lst->change && e->x >= 0
		&& e->y >= 0 && e->x < S_W && e->y < S_H)
		lst->change = 0;
	else if (e->button == SDL_BUTTON_RIGHT && e->x >= 0
		&& e->y >= 0 && e->x < S_W && e->y < S_H)
		lst->change = 1;
	else if (e->button == SDL_BUTTON_LEFT && e->x >= 0
		&& e->y >= 0 && e->x < S_W && e->y < S_H)
		search_fig(lst, e->x, e->y);
}
