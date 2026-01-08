/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:21:56 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/16 17:42:56 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*node;

	i = 0;
	if (lst == NULL)
		return (0);
	node = lst;
	while (node != NULL)
	{
		node = node -> next;
		i++;
	}
	return (i);
}
