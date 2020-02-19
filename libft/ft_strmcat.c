/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:09:53 by vkaron            #+#    #+#             */
/*   Updated: 2019/09/23 17:09:55 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmcat(char *s1, char *s2)
{
	char	*tmp;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((len1 + len2 + 1) == 0)
		return (0);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (i < len1)
	{
		tmp[i] = s1[i];
		++i;
	}
	while (*s2)
	{
		tmp[i++] = *s2;
		s2++;
	}
	tmp[i] = 0;
	return (tmp);
}
