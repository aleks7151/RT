/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_material1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:33:08 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 00:41:24 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	load_map(t_map *map, char *filename)
{
	map->map = 0;
	map->data = 0;
	if (!(map->name_map = ft_strdup("none")))
		ft_exit("STRDUP FAILED AGAIN");
	if (!filename)
		return ;
	free(map->name_map);
	map->map = IMG_Load(filename);
	if (map->map)
		map->data = (int*)(map->map->pixels);
	map->name_map = ft_strdup(filename);
}

int		set_name_mat(t_lst *lst, char *word)
{
	char **name;

	if (!word || !(*word))
		return (0);
	if (ft_strlen(word) > 17)
		return (0);
	if (!(name = ft_strsplit(word, ' ')))
		ft_exit("MALLOC FAILED:(");
	ft_strncpy(lst->scn->cur_mat->name, name[0], 18);
	return (free_words(name, 1));
}

int		set_diff_map_mat(t_lst *lst, char *word)
{
	char **filename;

	if (!word || !(*word))
		return (0);
	if (!(filename = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	load_map(&(lst->scn->cur_mat->diff_map), filename[0]);
	return (free_words(filename, 1));
}

int		set_norm_map_mat(t_lst *lst, char *word)
{
	char **filename;

	if (!word || !(*word))
		return (0);
	if (!(filename = ft_strsplit(word, ' ')))
		ft_exit("SPLIT BROKEN");
	load_map(&(lst->scn->cur_mat->norm_map), filename[0]);
	return (free_words(filename, 1));
}

int		set_mask_map_mat(t_lst *lst, char *word)
{
	char **filename;

	if (!word || !(*word))
		return (0);
	if (!(filename = ft_strsplit(word, ' ')))
		ft_exit("Not malloc");
	load_map(&(lst->scn->cur_mat->mask_map), filename[0]);
	return (free_words(filename, 1));
}
