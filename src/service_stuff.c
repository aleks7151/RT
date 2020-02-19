/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:26:30 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 15:49:20 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_exit(char *line)
{
	ft_putstr(line);
	ft_putchar('\n');
	exit(-1);
}

int		find_me_clrs(t_isec **csc, t_lst *l, t_trc trc, SDL_Color *col)
{
	if (init_trace(l, csc, trc, col))
		return (1);
	if (!l->shd)
	{
		col->r = 0;
		col->g = 0;
		col->b = 0;
		col->a = 0;
	}
	return (0);
}

int		free_scene_init(t_lst *lst)
{
	free_l(lst);
	ft_exit("Smells like invalid file spirit:(");
	return (-1);
}

int		free_init_sdl(t_lst *lst)
{
	close_sdl(lst);
	free_l(lst);
	ft_exit("BAD THINGS HAPPENING TO SDL");
	return (-1);
}

int		check_split_len(char **split)
{
	int		i;

	i = 0;
	if (!split)
		return (i);
	while (split[i])
		i++;
	return (i);
}
