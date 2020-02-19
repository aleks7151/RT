/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:15:01 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 19:08:58 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_vec(t_lst *l, int fsize, SDL_Rect *d, t_vec3 *v)
{
	char		*a;

	a = c_lim(get_fnbr_to_string(v->x));
	print_ttf(l->mimg, a, fsize, d);
	free(a);
	d->x += 50;
	a = c_lim(get_fnbr_to_string(v->y));
	print_ttf(l->mimg, a, fsize, d);
	free(a);
	d->x += 50;
	a = c_lim(get_fnbr_to_string(v->z));
	print_ttf(l->mimg, a, fsize, d);
	free(a);
}

void		draw_col(t_lst *l, int fsize, SDL_Rect *d, SDL_Color *c)
{
	char		*a;

	a = c_lim(get_inbr_to_string(c->r, ""));
	print_ttf(l->mimg, a, fsize, d);
	free(a);
	d->x += 50;
	a = c_lim(get_inbr_to_string(c->g, ""));
	print_ttf(l->mimg, a, fsize, d);
	free(a);
	d->x += 50;
	a = c_lim(get_inbr_to_string(c->b, ""));
	print_ttf(l->mimg, a, fsize, d);
	free(a);
}

void		draw_type_fig(t_lst *l, int fsize, int x, int y)
{
	SDL_Rect d;

	d.x = x;
	d.y = y;
	if (l->scn->cur_fig->type == sphere)
		print_ttf(l->mimg, "SPHERE", fsize, &d);
	else if (l->scn->cur_fig->type == plane)
		print_ttf(l->mimg, "PLANE", fsize, &d);
	else if (l->scn->cur_fig->type == conus)
		print_ttf(l->mimg, "CONUS", fsize, &d);
	else if (l->scn->cur_fig->type == cylinder)
		print_ttf(l->mimg, "CYLINDER", fsize, &d);
	else if (l->scn->cur_fig->type == inv_sph)
		print_ttf(l->mimg, "INVERT", fsize, &d);
}

/*
** light panel
*/

void		draw_text_menu3(t_lst *l)
{
	SDL_Rect	d;
	int			*data;
	int			h;

	data = (int *)l->mimg->pixels;
	h = -1;
	while (++h < S_W * S_H)
		data[h] = 0x88ffffff;
	print_ttf(l->mimg, "Light:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y));
	draw_type_lght(l, 14, l->mrect.x + 55, l->mrect.y);
	print_ttf(l->mimg, "position:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.x + 15));
	draw_vec(l, 14, set_rect(&d, l->mrect.x + 75,
		l->mrect.x + 15), &(l->scn->cur_lght->pos));
}

/*
** material panel
*/

void		draw_text_menu4(t_lst *l)
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
	print_ttf(l->mimg, "Material:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y - 95));
	print_ttf(l->mimg, mat->name, 14, set_rect(&d, l->mrect.x + 75,
		l->mrect.y - 95));
	print_ttf(l->mimg, "color:", 14, set_rect(&d, l->mrect.x - 5,
		l->mrect.y - 75));
	draw_col(l, 14, set_rect(&d, l->mrect.x + 75,
		l->mrect.y - 75), &(l->scn->cur_fig->mat->col));
}
