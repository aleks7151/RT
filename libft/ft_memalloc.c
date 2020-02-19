/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:22:55 by vabraham          #+#    #+#             */
/*   Updated: 2019/09/17 22:06:49 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *str;

	if (size + 1 <= 0)
		return (NULL);
	str = malloc((size));
	if (!str)
		return (NULL);
	ft_memset(str, 0, size);
	return (str);
}
