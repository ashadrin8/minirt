/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:00:11 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/20 14:21:28 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (lst == NULL)
		return ;
	node = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (node -> next != NULL)
		node = node -> next;
	node -> next = new;
}
