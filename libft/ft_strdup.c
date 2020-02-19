/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:08:01 by vkaron            #+#    #+#             */
/*   Updated: 2019/09/23 17:08:04 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	size_t	len;
	char	*tmp;
	size_t	i;

	len = ft_strlen(str);
	if (len == 0 || (len + 1) == 0)
		return (0);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = 0;
	return (tmp);
}
