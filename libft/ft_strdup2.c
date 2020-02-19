/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:01:09 by vkaron            #+#    #+#             */
/*   Updated: 2019/10/15 22:40:49 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup2(const char *s1)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen((char*)s1) + 1));
	if (tmp != 0)
	{
		i = 0;
		while (s1[i])
		{
			tmp[i] = s1[i];
			i++;
		}
		tmp[i] = 0;
	}
	return (tmp);
}
