/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:14:53 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/19 15:50:40 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	ft_atof(char *f)
{
	char	**num;
	float	res;
	int		i;
	int		len;

	res = 0.0f;
	if (!(num = ft_strsplit(f, '.')))
		ft_exit("Not malloc");
	if (num[1])
	{
		len = ft_strlen(num[1]);
		i = ft_atoi(num[1]);
		res = (float)i / powf(10, len);
	}
	i = ft_atoi(num[0]);
	res += i;
	free_words(num, 0);
	return (res);
}

void	ret(t_lst *lst)
{
	mult_m3(&lst->scn->cam_pos0, lst->scn->cam_pos0, lst->camera_z);
	mult_m3(&lst->scn->cam_pos0, lst->scn->cam_pos0, lst->camera_x);
	mult_m3(&lst->scn->cam_pos0, lst->scn->cam_pos0, lst->camera_y);
	lst->scn->cam_pos = plus_vec3(lst->scn->cam_pos, lst->scn->cam_pos0);
	lst->scn->cam_pos0.x = 0;
	lst->scn->cam_pos0.y = 0;
	lst->scn->cam_pos0.z = 0;
}

int		close_free(int fd, char **line, char **word, int ret)
{
	free_word_line(line, word);
	free(line);
	line = NULL;
	close(fd);
	return (ret);
}

int		close_dir(int fd, char **line, int ret)
{
	free(line);
	line = NULL;
	close(fd);
	return (ret);
}
