/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:07:41 by vkaron            #+#    #+#             */
/*   Updated: 2019/09/23 20:47:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t n)
{
	size_t	len;
	char	*tmp;
	size_t	i;

	len = ft_strlen(str);
	if (len > n)
		len = n;
	if ((len + 1) == 0)
		return (0);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = 0;
	return (tmp);
}
