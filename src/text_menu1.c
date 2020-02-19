/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_menu1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:56:43 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/14 18:07:05 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** scene panel
*/

void	draw_text_menu1(t_lst *l)
{
	SDL_Rect	d;
	int			*data;
	int			h;

	data = (int *)l->mimg->pixels;
	h = -1;
	while (++h < S_W * S_H)
		data[h] = 0x88ffffff;
	print_ttf(l->mimg, "Shader:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y));
	draw_shader(l, 14, l->mrect.x + 55, l->mrect.y);
	print_ttf(l->mimg, "Camera:", 14, set_rect(&d, l->mrect.x + 35,
		l->mrect.y + 15));
	print_ttf(l->mimg, "position:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y + 30));
	draw_cam_pos(l, 14, l->mrect.x + 75, l->mrect.y + 30);
}

void	button_bg(int *data, SDL_Rect *d, int fig)
{
	int x;
	int y;

	y = d->y - 5;
	while (y < d->y + 18)
	{
		x = d->x - 5;
		while (x < d->x + 70)
		{
			if (fig == -1)
				data[y * S_W + x] = 0x99ff5500;
			else
				data[y * S_W + x] = 0x99ff0000;
			++x;
		}
		++y;
	}
}

void	draw_cre_button(t_lst *l, int fig, SDL_Rect *d)
{
	int			*data;

	data = (int *)l->mimg->pixels;
	button_bg(data, d, fig);
	if (fig == -1)
		print_ttf(l->mimg, "NEXT MAT", 14, d);
	else if (fig == sphere)
		print_ttf(l->mimg, "SPHERE", 14, d);
	else if (fig == plane)
		print_ttf(l->mimg, "PLANE", 14, d);
	else if (fig == conus)
		print_ttf(l->mimg, "CONUS", 14, d);
	else if (fig == cylinder)
		print_ttf(l->mimg, "CYLINDER", 14, d);
	else if (fig == inv_sph)
		print_ttf(l->mimg, "INVERT", 14, d);
}

/*
** figure panel
*/

void	draw_text_menu2_0(t_lst *l, SDL_Rect d)
{
	draw_type_fig(l, 14, l->mrect.x + 55, l->mrect.y);
	print_ttf(l->mimg, "position:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y + 15));
	draw_vec(l, 14, set_rect(&d, l->mrect.x + 75,
		l->mrect.y + 15), &(l->scn->cur_fig->pos));
	print_ttf(l->mimg, "rotation:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y + 30));
	print_ttf(l->mimg, "CREATE FIGURE:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y + 50));
	draw_vec(l, 14, set_rect(&d, l->mrect.x + 75,
		l->mrect.y + 30), &(l->scn->cur_fig->alpha));
	draw_cre_button(l, sphere, set_rect(&d, l->mrect.x,
		l->mrect.y + 70));
	draw_cre_button(l, plane, set_rect(&d, l->mrect.x + 85,
		l->mrect.y + 70));
	draw_cre_button(l, conus, set_rect(&d, l->mrect.x,
		l->mrect.y + 100));
	draw_cre_button(l, inv_sph, set_rect(&d, l->mrect.x + 85,
		l->mrect.y + 100));
	draw_cre_button(l, cylinder, set_rect(&d, l->mrect.x,
		l->mrect.y + 130));
	draw_cre_button(l, -1, set_rect(&d, l->mrect.x + 85,
		l->mrect.y + 130));
}

void	draw_text_menu2(t_lst *l)
{
	SDL_Rect	d;
	int			*data;
	int			h;

	data = (int *)l->mimg->pixels;
	h = -1;
	while (++h < S_W * S_H)
		data[h] = 0x88ffffff;
	print_ttf(l->mimg, "Figure:", 14, set_rect(&d, l->mrect.x - 5,
	l->mrect.y));
	draw_text_menu2_0(l, d);
}
