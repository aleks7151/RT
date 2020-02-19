/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_menu2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 18:06:26 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 15:48:06 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_type_lght(t_lst *l, int fsize, int x, int y)
{
	SDL_Rect d;

	d.x = x;
	d.y = y;
	if (l->scn->cur_lght->type == ambient)
		print_ttf(l->mimg, "AMBIENT", fsize, &d);
	else if (l->scn->cur_lght->type == direct)
		print_ttf(l->mimg, "DIRECT", fsize, &d);
	else if (l->scn->cur_lght->type == point)
		print_ttf(l->mimg, "POINT", fsize, &d);
	else if (l->scn->cur_lght->type == lconus)
		print_ttf(l->mimg, "CONUS", fsize, &d);
}

SDL_Surface	*hide_menu_for_screen(t_lst *lst)
{
	SDL_Surface	*surface;

	if (lst->show_menu)
	{
		rain(lst);
		post_effects(lst);
	}
	surface = scrin0(lst, -1, -1, 0);
	return (surface);
}

void		draw_text_help0(t_lst *l)
{
	SDL_Rect	d;

	print_ttf(l->mimg, "use/next figure - \"f\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 110));
	print_ttf(l->mimg, "use/next light - \"g\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 125));
	print_ttf(l->mimg, "rotate current figure - \"TY IO KL\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 140));
	print_ttf(l->mimg, "pick figure - \"right mouse click\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 155));
	print_ttf(l->mimg, "move figure - \"left mouse click+move+wheel\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 170));
	print_ttf(l->mimg, "save scane - \"backspace\"", 14,
		set_rect(&d, l->mrect.x + 255, l->mrect.y + 20));
	print_ttf(l->mimg, "screenshots- \"Enter\"", 14,
		set_rect(&d, l->mrect.x + 255, l->mrect.y + 35));
	print_ttf(l->mimg, "post effects - \"[\", \"]\"", 14,
		set_rect(&d, l->mrect.x + 255, l->mrect.y + 50));
	print_ttf(l->mimg, "exit - \"ESC\"", 14,
		set_rect(&d, l->mrect.x + 255, l->mrect.y + 75));
}

/*
** help panel
*/

void		draw_text_help(t_lst *l)
{
	SDL_Rect	d;
	int			*data;
	t_mat		*mat;
	int			h;

	data = (int *)l->mimg->pixels;
	h = -1;
	while (++h < S_W * S_H)
		data[h] = 0x88ffffff;
	mat = l->scn->cur_fig->mat;
	print_ttf(l->mimg, "HELP:", 14, set_rect(&d, l->mrect.x + 5,
		l->mrect.y + 5));
	print_ttf(l->mimg, "show/hide HELP - \"x\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 20));
	print_ttf(l->mimg, "show/hide menu - \"F6\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 35));
	print_ttf(l->mimg, "change shading - \"F5\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 50));
	print_ttf(l->mimg, "show/hide shadow - \"space\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 65));
	print_ttf(l->mimg, "move camera - \"arrow\",\"<\",\">\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 80));
	print_ttf(l->mimg, "rotate camera - \"QE WS AD\"", 14,
		set_rect(&d, l->mrect.x + 5, l->mrect.y + 95));
	draw_text_help0(l);
}

int			show_help(t_lst *lst, SDL_Rect *r)
{
	r->x = 0;
	r->y = 0;
	lst->mrect.y = 10;
	if (lst->show_help)
	{
		r->w = S_W - 20;
		r->h = S_H - 20;
		draw_text_help(lst);
		SDL_BlitSurface(lst->mimg, r, lst->img, &lst->mrect);
		return (1);
	}
	r->w = 230;
	r->h = 85;
	return (0);
}
