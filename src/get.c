/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:22:12 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 15:57:24 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*get_inbr_to_string(int num, char *s)
{
	char *b;
	char *c;

	b = ft_itoa(num);
	if (!(c = ft_strjoin(b, s)))
		ft_exit("STRJOIN FAILED");
	free(b);
	return (c);
}

char	*get_fnbr_to_string(float num)
{
	float	tmp;
	char	*result;
	char	*buf1;
	char	*buf2;

	tmp = num - (float)(int)num;
	if (tmp < 0)
		tmp *= -1;
	while (tmp != (float)(int)tmp)
		tmp *= 10;
	buf1 = get_inbr_to_string((int)num, ".");
	buf2 = get_inbr_to_string((tmp), "");
	if (!(result = ft_strjoin(buf1, buf2)))
		ft_exit("STRJOIN FAILED IN FNBR");
	free(buf1);
	free(buf2);
	return (result);
}

int		get_file_scene(char *str_scene)
{
	int		fd;
	int		num_scene;
	char	*str;
	char	*buf;

	str = "scenes/scene";
	num_scene = 0;
	while (1)
	{
		if (str_scene)
			free(str_scene);
		buf = get_inbr_to_string(num_scene, "");
		if (!(str_scene = ft_strjoin(str, buf)))
			ft_exit("STRJOIN FAILED");
		free(buf);
		if ((fd = open(str_scene, O_WRONLY)) == -1)
			break ;
		close(fd);
		num_scene++;
	}
	fd = open(str_scene, O_WRONLY | O_CREAT);
	ft_putstr(str_scene);
	free(str_scene);
	ft_putchar('\n');
	return (fd);
}

char	*get_thre_int(int x, int y, int z)
{
	char *s;
	char *tmp;
	char *buf;

	tmp = get_inbr_to_string(x, "");
	s = tmp;
	if (!(tmp = ft_strjoin(s, " ")))
		ft_exit("STRJOIN FAILED");
	free(s);
	s = tmp;
	buf = get_inbr_to_string(y, "");
	if (!(tmp = ft_strjoin(s, buf)))
		ft_exit("STRJOIN FAILED");
	free(buf);
	free(s);
	s = tmp;
	if (!(tmp = ft_strjoin(s, " ")))
		ft_exit("STRJOIN FAILED");
	free(s);
	s = tmp;
	buf = get_inbr_to_string(z, "");
	if (!(tmp = ft_strjoin(s, buf)))
		ft_exit("STRJOIN FAILED");
	free_get(&buf, &s);
	return (tmp);
}

char	*get_thre_float(float x, float y, float z)
{
	char *s;
	char *tmp;
	char *buf;

	tmp = get_fnbr_to_string(x);
	s = tmp;
	if (!(tmp = ft_strjoin(s, " ")))
		ft_exit("STRJOIN FAILED");
	free(s);
	s = tmp;
	buf = get_fnbr_to_string(y);
	if (!(tmp = ft_strjoin(s, buf)))
		ft_exit("STRJOIN FAILED");
	free(buf);
	free(s);
	s = tmp;
	if (!(tmp = ft_strjoin(s, " ")))
		ft_exit("STRJOIN FAILED");
	free(s);
	s = tmp;
	buf = get_fnbr_to_string(z);
	if (!(tmp = ft_strjoin(s, buf)))
		ft_exit("STRJOIN FAILED");
	free_get(&buf, &s);
	return (tmp);
}
