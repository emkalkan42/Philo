/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:38:42 by emkalkan          #+#    #+#             */
/*   Updated: 2024/10/06 19:03:16 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*el;

	if (lst[0] == NULL)
		lst[0] = new;
	else
	{
		el = lst[0];
		while (el -> next != NULL)
		{
			el = el -> next;
		}
		el -> next = new;
	}
}
