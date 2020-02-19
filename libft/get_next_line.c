/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:23:41 by vkaron            #+#    #+#             */
/*   Updated: 2019/10/15 21:26:47 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_elem(char **elem)
{
	if (*elem)
		free(*elem);
	*elem = 0;
	return (-1);
}

static int	add_to_line(char **line, char **tile)
{
	size_t	len;
	char	*tmp;

	if (!(*tile))
		return (0);
	if ((len = ft_strfind(*tile, '\n')) == 0)
		len = ft_strlen(*tile);
	else
		--len;
	tmp = ft_strndup(*tile, len);
	if (!tmp)
	{
		free_elem(tile);
		return (0);
	}
	*line = tmp;
	(*line)[len] = 0;
	tmp = ft_strrdup(*tile, ft_strlen(*tile) - len);
	free_elem(tile);
	if (tmp)
		*tile = tmp;
	return (1);
}

static int	read_to_tile(const int fd, char **tile)
{
	int		n;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	while (ft_strfind(*tile, '\n') == 0)
	{
		n = read(fd, buffer, BUFF_SIZE);
		if ((n == 0) && ((*tile == 0) || (**tile == 0)))
			return (0);
		if (n == 0)
			return (1);
		if (n == -1)
			return (free_elem(tile));
		buffer[n] = 0;
		if (!*tile)
			tmp = ft_strdup(buffer);
		else
			tmp = ft_strmcat(*tile, buffer);
		free_elem(tile);
		if (!tmp)
			return (-1);
		*tile = tmp;
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*tiles[65536] = {0};
	int			res;

	if (fd < 0 || fd > 65536 || !line)
		return (-1);
	res = read_to_tile(fd, &tiles[fd]);
	if (res <= 0)
	{
		free_elem(&tiles[fd]);
		return (res);
	}
	res = add_to_line(line, &tiles[fd]);
	return (res);
}
