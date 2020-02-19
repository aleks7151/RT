/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 00:21:35 by vkaron            #+#    #+#             */
/*   Updated: 2019/10/15 22:38:56 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

static void	del_map(char **map, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(map[i]);
		map[i++] = 0;
	}
	free(map);
	map = 0;
}

static char	*get_word(char *s, char c)
{
	int		len;
	char	*tmp;
	int		i;

	len = 0;
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		break ;
	}
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp)
		tmp = ft_strncpy(tmp, s, len);
	tmp[len] = 0;
	return (tmp);
}

static char	**get_words(char *s, char c, char **map, int words)
{
	int		i;

	i = 0;
	while (i < words)
	{
		map[i] = get_word(s, c);
		if (!map[i])
		{
			del_map(map, i);
			return (0);
		}
		while (*s == c)
			s++;
		s += ft_strlen(map[i]);
		i++;
	}
	map[i] = 0;
	return (map);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**map;
	char	*src;
	int		words;

	if (!s || !(src = ft_strdup2(s)))
		return (0);
	words = count_words(src, c);
	map = (char **)malloc(sizeof(char *) * (words + 1));
	if (map)
		map = get_words(src, c, map, words);
	free(src);
	return (map);
}
