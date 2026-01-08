/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:42:08 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/17 21:52:56 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	node = *lst;
	while (node != NULL)
	{
		temp = node -> next;
		del(node -> content);
		free(node);
		node = temp;
	}
	*lst = NULL;
}
