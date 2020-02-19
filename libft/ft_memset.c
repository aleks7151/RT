/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:41:43 by vabraham          #+#    #+#             */
/*   Updated: 2019/09/16 19:45:53 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int n, size_t size)
{
	char *str;

	str = (char *)dest;
	while (size > 0)
	{
		str[size - 1] = (char)n;
		size--;
	}
	return (dest);
}
