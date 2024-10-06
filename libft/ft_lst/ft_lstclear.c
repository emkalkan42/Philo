/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:41:16 by emkalkan          #+#    #+#             */
/*   Updated: 2024/10/06 19:03:38 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*el;
	t_list	*elem;

	if (lst != 0 && lst[0] != 0)
	{
		el = lst[0];
		while (el -> next != NULL)
		{
			del(el -> content);
			elem = el;
			el = el -> next;
			free(elem);
		}
		del(el -> content);
		free(el);
		lst[0] = NULL;
	}
}
