/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:43:28 by emkalkan          #+#    #+#             */
/*   Updated: 2024/10/06 19:02:41 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*sors;
	size_t		i;

	dst = dest;
	sors = src;
	i = -1;
	if (dst == 0 && sors == 0)
		return (NULL);
	if (dst < sors || sors + n < dst)
	{
		while (++i < n)
		{
			dst[i] = sors[i];
		}
	}
	else
	{
		while (n > 0)
		{
			dst[n - 1] = sors[n - 1];
			n--;
		}
	}
	return (dest);
}
