/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:06:24 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/20 14:23:57 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;
	void	*f_variable;

	if (!f || !lst || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		f_variable = f(lst -> content);
		new_node = ft_lstnew(f_variable);
		if (!new_node)
		{
			del(f_variable);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node),
		lst = lst -> next;
	}
	return (new_list);
}
// t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list *node;
// 	t_list *new_node;
// 	t_list **new_list;
// 	t_list *malloc_var;
// 	void *f_var;

// 	node = lst;
// 	if (!lst)
// 		return (NULL);
// 	new_node = NULL;
// 	new_list = &new_node;
// 	while (node != NULL)
// 	{
// 		f_var = f(node->content);
// 		new_node = ft_lstnew(f_var);
// 		malloc_var = (t_list *)malloc (sizeof(t_list) * 1);
// 		if (malloc_var == 0)
// 		{
// 			ft_lstclear(new_list, del);
// 			return (NULL);
// 		}
// 		malloc_var -> next = NULL;
// 		if (!new_list)
// 			new_node = malloc_var;
// 		else
// 		{
// 			new_node -> next = malloc_var;
// 			new_node = malloc_var;
// 		}
// 		f_var = f(node -> content);
// 		malloc_var -> content = f_var;
// 		node = node -> next;
// 		new_node = new_node -> next;
// 	}
// 	return (*new_list);
// }
	// if (!f_var)
		// {
		// 	ft_lstclear(&new_list, del);
		// 	return (NULL);
		// }
