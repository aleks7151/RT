/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:37:12 by vkaron            #+#    #+#             */
/*   Updated: 2019/09/08 13:56:33 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	if (tmp_s1 == tmp_s2)
		return (0);
	while (*tmp_s1 || *tmp_s2)
	{
		if (*tmp_s1 != *tmp_s2)
			return ((int)(*tmp_s1 - *tmp_s2));
		tmp_s1++;
		tmp_s2++;
	}
	return (0);
}
