/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:24:06 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 15:52:49 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		mult(t_lst *lst, t_trc *trc, int x, int y)
{
	SDL_Color	col;
	t_isec		*cisec;

	cisec = NULL;
	trc->d.x = (float)x * RATIO / H_W;
	trc->d.y = (float)y / H_H;
	trc->d.z = lst->scn->cam_focus_dist;
	mult_m3(&trc->d, trc->d, lst->camera_z);
	mult_m3(&trc->d, trc->d, lst->camera_x);
	mult_m3(&trc->d, trc->d, lst->camera_y);
	lst->depth_refr = REFR_DEPTH;
	col = trace(lst, *trc, RECURCE_DEPTH, cisec);
	lst->data[(S_H - y - H_H - 1) * S_W + x + H_W] =
		(col.r << 16) + (col.g << 8) + col.b;
	lst->data_dop[(S_H - y - H_H - 1) * S_W + x + H_W] =
		lst->data[(S_H - y - H_H - 1) * S_W + x + H_W];
}

void		*pixel(void *l)
{
	t_lst	*lst;
	int		x;
	int		y;
	t_trc	trc;

	lst = (t_lst*)l;
	trc.min = 1.0f;
	trc.max = INFINITY;
	y = -S_H / 2 + lst->pot * S_H / POT - 1;
	trc.o = set_vec3(lst->scn->cam_pos0);
	mult_m3(&trc.o, trc.o, lst->camera_z);
	mult_m3(&trc.o, trc.o, lst->camera_x);
	mult_m3(&trc.o, trc.o, lst->camera_y);
	trc.o = plus_vec3(trc.o, lst->scn->cam_pos);
	while (++y < -S_H / 2 + (lst->pot + 1) * S_H / POT)
	{
		x = -S_W / 2 - 1;
		while (++x < S_W / 2)
			mult(lst, &trc, x, y);
	}
	return (0);
}

void		rain(t_lst *lst)
{
	t_lst			data[POT];
	pthread_t		threads[POT];
	pthread_attr_t	attr;
	int				rc;
	void			*status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	lst->pot = -1;
	while (++(lst->pot) < POT)
	{
		ft_memcpy((void*)&data[lst->pot], (void *)lst, sizeof(t_lst));
		rc = pthread_create(&threads[lst->pot],
			NULL, pixel, (void *)(&data[lst->pot]));
	}
	pthread_attr_destroy(&attr);
	lst->pot = -1;
	while (++(lst->pot) < POT)
		rc = pthread_join(threads[lst->pot], &status);
}

static void	check_segv(char *file)
{
	int		fd;
	int		ret;
	char	buff[6];

	fd = open(file, O_RDONLY);
	if (!fd)
		ft_exit("U TRYINA SEGV ME?");
	ret = read(fd, buff, 5);
	if (!ret || ret < 0)
		ft_exit("U GIVING BAD FILES ARENT YA");
}

int			main(int ac, char *av[])
{
	t_lst		*lst;

	check_segv(av[1]);
	if (ac == 2)
	{
		if (!(lst = (t_lst *)ft_memalloc(sizeof(t_lst))))
			ft_exit("Failed to alloc t_list");
		if (!scene_init(lst, av[1]))
			return (free_scene_init(lst));
		if (!init_sdl(lst))
			return (free_init_sdl(lst));
		sdl_cycle(lst);
		close_sdl(lst);
		free_l(lst);
	}
	return (0);
}
