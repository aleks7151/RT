/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:10:52 by vkaron            #+#    #+#             */
/*   Updated: 2019/09/23 17:11:28 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strfind(char *str, char sym)
{
	size_t	pos;

	if (!str)
		return (0);
	pos = 1;
	while (*str)
	{
		if (*str == sym)
			return (pos);
		++pos;
		++str;
	}
	return (0);
}
