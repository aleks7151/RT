/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:52:08 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 15:47:24 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	else if (bpp == 2)
		*(Uint16 *)p = pixel;
	else if (bpp == 3)
	{
		p[1] = (pixel >> 8) & 0xff;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
	}
	else if (bpp == 4)
		*(Uint32 *)p = pixel;
}

Uint32		getpixel(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	else
		return (0);
}

SDL_Surface	*scrin0(t_lst *lst, int i, int j, Uint8 red)
{
	SDL_Surface	*surface;
	Uint8		blue;
	Uint32		pixel;
	Uint8		green;

	surface = SDL_CreateRGBSurfaceFrom(lst->img->pixels, lst->img->w,
		lst->img->h, lst->img->format->BitsPerPixel, lst->img->w *
		lst->img->format->BytesPerPixel, lst->img->format->Rmask,
		lst->img->format->Gmask, lst->img->format->Bmask,
		lst->img->format->Amask);
	while (++i < surface->h)
	{
		j = -1;
		while (++j < surface->w)
		{
			red = 0;
			green = 0;
			blue = 0;
			pixel = getpixel(surface, j, i);
			SDL_GetRGB(pixel, surface->format, &red, &green, &blue);
			pixel = SDL_MapRGB(surface->format, red, green, blue);
			putpixel(surface, j, i, pixel);
		}
	}
	return (surface);
}

int			scrin(t_lst *lst)
{
	SDL_Surface	*surface;
	char		*str;
	char		*tmp;
	int			fd;

	surface = hide_menu_for_screen(lst);
	while (1)
	{
		str = get_inbr_to_string(lst->num_file_for_screen, "");
		if (!(tmp = ft_strjoin("screenshots/screen", str)))
			ft_exit("Not malloc");
		free(str);
		if ((fd = open(tmp, O_RDONLY)) == -1)
			break ;
		close(fd);
		free(tmp);
		lst->num_file_for_screen += 1;
	}
	IMG_SavePNG(surface, tmp);
	free(tmp);
	SDL_FreeSurface(surface);
	lst->num_file_for_screen += 1;
	if (lst->show_menu)
		show_menu(lst);
	return (0);
}

int			key_press_dop(SDL_Keycode key, t_lst *lst)
{
	if (key == SDLK_LEFT)
		lst->scn->cam_pos0.x -= 1;
	else if (key == SDLK_RIGHT)
		lst->scn->cam_pos0.x += 1;
	else if (key == SDLK_UP)
		lst->scn->cam_pos0.z += 1;
	else if (key == SDLK_DOWN)
		lst->scn->cam_pos0.z -= 1;
	else if (key == SDLK_COMMA)
		lst->scn->cam_pos0.y -= 1;
	else if (key == SDLK_PERIOD)
		lst->scn->cam_pos0.y += 1;
	else if (key == SDLK_i)
		multy_x(lst, 3);
	else if (key == SDLK_o)
		multy_x(lst, -3);
	else if (key == SDLK_k)
		multy_y(lst, -3);
	return (key_press0(key, lst));
}
