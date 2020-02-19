/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:37:10 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/21 17:42:30 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*is_sign(int *sign, char *str, long long *res, int *len)
{
	*res = 0;
	*len = 0;
	*sign = 1;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

static int	check_border(long long res, int sign, int len)
{
	if (((unsigned long long)res > 0x7FFFFFFFFFFFFFFF && sign == 1)
		|| (len > 19 && sign == 1))
		return (-1);
	if (((unsigned long long)res > 0x7FFFFFFFFFFFFFFF && sign == -1)
		|| (len > 19 && sign == -1))
		return (0);
	return (res * sign);
}

int			ft_atoi(char *str)
{
	long long	res;
	int			sign;
	int			len;
	char		*tmp;

	if ((*str == 0) || (*str == 27))
		return (0);
	tmp = (char *)str;
	while (ft_isspace(*tmp))
		tmp++;
	tmp = is_sign(&sign, tmp, &res, &len);
	while (*tmp)
	{
		if ((*tmp < '0') || (*tmp > '9'))
			break ;
		res = (res * 10) + (*tmp - '0');
		tmp++;
		len++;
	}
	return (check_border(res, sign, len));
}
