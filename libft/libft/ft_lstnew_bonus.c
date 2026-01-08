/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:18:31 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/13 20:30:51 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node -> content = content;
	node -> next = NULL;
	return (node);
}
// typedef char t_byte;
// typedef some_data_type nikname;
// typedef struct s_list
// {
// 	void *content;
// 	struct s_list *next;
// }	t_list;
// int main()
// {
// 	t_list *flower;
// 	flower = malloc(sizeof(t_list))
// 	node->next
// }
// typedef struct s_list
// {
// 	void *content;
// 	struct s_list *next;
// }	t_list;
