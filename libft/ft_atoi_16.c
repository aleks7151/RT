/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:37:10 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/21 17:43:17 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	from_hex(char c)
{
	const char	*hex1 = "0123456789abcdef";
	const char	*hex2 = "0123456789ABCDEF";
	int			i;

	i = 0;
	while (hex1[i])
	{
		if (c == hex1[i] || c == hex2[i])
			return (i);
		++i;
	}
	return (-1);
}

int			ft_atoi_16(char *str)
{
	long long	res;
	int			len;
	char		*tmp;
	int			dec;

	if ((*str == 0) || (*str == 27))
		return (0);
	tmp = str;
	while (ft_isspace(*tmp))
		tmp++;
	res = 0;
	len = 0;
	while (*tmp)
	{
		dec = from_hex(*tmp);
		if (dec < 0)
			break ;
		res = (res * 16) + dec;
		tmp++;
		len++;
	}
	return (res);
}
