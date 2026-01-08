/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:53:10 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/12 13:38:36 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*space;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	space = (char *)malloc(sizeof(char) * len + 1);
	if (space == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		space[i] = f(i, s[i]);
		i++;
	}
	space[i] = '\0';
	return (space);
}

// char *pupupu(size_t i, char ale)
// {
// 	char *str = "i love jesus";

// 	str[i] = ale;
// 	return (str);
// }

// int main()
// {
// 	char ale;
// 	size_t i;
// 	char *str;

// 	ale = 'h';
// 	i = 0;
// 	printf("%s", ft_strmapi((char const)str, pupupu(i, ale)));
// 	return (0);
// }
