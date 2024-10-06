/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:12:16 by emkalkan          #+#    #+#             */
/*   Updated: 2024/10/06 19:06:56 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*ptr;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	len++;
	ptr = (char *)malloc(len * sizeof(char));
	if (ptr)
	{
		while (i < len)
		{
			ptr[i] = s[i];
			i++;
		}
		return (ptr);
	}
	else
		return (NULL);
}
