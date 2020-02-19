/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_menu0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:56:09 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/17 22:15:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_ttf(SDL_Surface *sdest, char *msg, int size, SDL_Rect *dest)
{
	SDL_Color	col;
	TTF_Font	*fnt;
	SDL_Surface	*stext;
	const char	*f = "prgres/courier.ttf";

	col = (SDL_Color){0, 0, 0, 255};
	fnt = NULL;
	fnt = TTF_OpenFont(f, size);
	if (!fnt)
		printf("TTF_OpenFontRW: %s\n", TTF_GetError());
	stext = TTF_RenderText_Blended(fnt, msg, col);
	SDL_BlitSurface(stext, NULL, sdest, dest);
	SDL_FreeSurface(stext);
	TTF_CloseFont(fnt);
}

SDL_Rect	*set_rect(SDL_Rect *rect, int x, int y)
{
	rect->x = x;
	rect->y = y;
	return (rect);
}

void		draw_shader(t_lst *l, int fsize, int x, int y)
{
	SDL_Rect d;

	d.x = x;
	d.y = y;
	if (!l->shd)
		print_ttf(l->mimg, "SIMPLE", fsize, &d);
	else if (l->shd == TEXTURE)
		print_ttf(l->mimg, "TRASPARE", fsize, &d);
	else if (l->shd == TRASPARENT)
		print_ttf(l->mimg, "TEXTURE", fsize, &d);
	else if (l->shd == REFRLECT)
		print_ttf(l->mimg, "REFRLECT", fsize, &d);
	else if (l->shd == REFRACT)
		print_ttf(l->mimg, "REFRACT", fsize, &d);
	d.x += 70;
	if (l->scn->shadow)
		print_ttf(l->mimg, "SHW ON", fsize, &d);
	else
		print_ttf(l->mimg, "SHW OFF", fsize, &d);
}

char		*c_lim(char *a)
{
	int i;

	i = 0;
	while (a[i])
	{
		if (a[i] == '.')
		{
			a[i + 2] = 0;
			break ;
		}
		++i;
	}
	return (a);
}

void		draw_cam_pos(t_lst *l, int fsize, int x, int y)
{
	SDL_Rect	d;
	char		*a;

	d.x = x;
	d.y = y;
	a = c_lim(get_fnbr_to_string(l->scn->cam_pos0.x + l->scn->cam_pos.x));
	print_ttf(l->mimg, a, fsize, &d);
	free(a);
	d.x += 50;
	a = c_lim(get_fnbr_to_string(l->scn->cam_pos0.y + l->scn->cam_pos.y));
	print_ttf(l->mimg, a, fsize, &d);
	free(a);
	d.x += 50;
	a = c_lim(get_fnbr_to_string(l->scn->cam_pos0.z + l->scn->cam_pos.z));
	print_ttf(l->mimg, a, fsize, &d);
	free(a);
}
