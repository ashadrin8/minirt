/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:27:43 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/23 16:28:40 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static char	*part_of_it(char const *s, int start, int end);
static int	strnum(char const *s, char c);
static int	start(const char *s, char c, int word);
static int	end(const char *s, char c, int word);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**space;

	if (!s)
		return (NULL);
	space = (char **)malloc((strnum(s, c) + 1) * sizeof(char *));
	if (space == NULL)
		return (NULL);
	i = 0;
	while (i < strnum(s, c))
	{
		space[i] = part_of_it(s, start(s, c, i + 1), end(s, c, i + 1));
		if (!space[i])
		{
			j = 0;
			while (j < i)
				free(space[j++]);
			free(space);
			return (NULL);
		}
		i++;
	}
	return (space[i] = NULL, space);
}

static int	strnum(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*part_of_it(char const *s, int start, int end)
{
	char	*thing;
	int		i;

	thing = (char *)malloc(sizeof(char) * (end - start + 2));
	if (thing == NULL)
		return (NULL);
	i = 0;
	while (i < (end - start + 1))
	{
		thing[i] = s[start + i];
		i++;
	}
	thing[i] = '\0';
	return (thing);
}

static int	start(const char *s, char c, int word)
{
	int	i;
	int	start;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (wordcount < word)
	{
		while (s[i] == c && s[i])
			i++;
		if ((i == 0 && s[i] != c)
			|| (i > 0 && s[i] != c && (s[i - 1] == c)))
			start = i;
		while (s[i] != c && s[i])
			i++;
		wordcount++;
	}
	return (start);
}

static int	end(const char *s, char c, int word)
{
	int	i;
	int	end;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (wordcount < word)
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
			i++;
		if (i > 0 && ((s[i] == '\0' && s[i -1] != c)
				|| (s[i] == c && s[i -1] != c)))
			end = i - 1;
		wordcount++;
	}
	return (end);
}

// static void	free_split (char **array, int count)
// {
// 	int	i;
// 	if (!array)
// 		return;
// 	i = 0;
// 	while (i < count)
// 	{
// 		if (array[i])
// 			free(array[i]);
// 		i++;
// 	}
// 	free (array);
// }
// #include <stdio.h>
// int main ()
// {
// 	int i;
// 	char **res = ft_split("      split       this for   me  !       ", ' ');
// 	i = 0;
// 	while (res[i] != NULL)
// 		printf("%-32.4s\n", res[i++]);
// }
// #include <stdio.h>
// int main ()
// {
// 	char *str = " hello ";
// 	char del = ' ';
// 	int start = count_start(str, del, 1);
// 	int end = count_end(str, del, 1);
// 	printf("%s", part_of_it (str, start, end));
// }
// #include <stdio.h>
// int main()
// {
// 	printf("end: %d", count_end(",,hello, world", ',', 2));
// }
// char *part_of_it (char const *s, char c)
// {
// 	int start;
// 	int end;
// 	int i;
// 	char *substring;
// 	i = 0;
// 	while (s[i] == c)
// 			i++;
// 		if ((s[i] != c) && (s[i-1] == c || i == 0))
// 		{
// 			start = i;
// 			while (s[i] != c)
// 				i++;
// 			end = i - 1;
// 			substring = (char *)malloc (sizeof(char) * (end - start + 2));
// 			if (substring == NULL)
// 				return (NULL);
// 			i = 0;
// 			while (substring[i] != '\0')
// 	}
// }
// char **ft_split(char const *s, char c)
// {
	// int start;
	// int end;
	// int i;
	// int j;
	// int count;
	// char **space;
	// char *substring;
	// space = (char **)malloc (strnum(s, c) + 1 * sizeof(char *));
	// if (space == NULL)
	// 	return (NULL);
	// i = 0;
	// count = 0;
	// while (s[i] != '\0')
	// {
	// 	while (s[i] == c)
	// 		i++;
	// 	if ((s[i] != c) && (s[i-1] == c || i == 0))
	// 	{
	// 		start = i;
	// 		while (s[i] != c)
	// 			i++;
	// 		end = i - 1;
	// 		substring = (char *)malloc (sizeof(char) * (end - start + 2));
	// 		if (substring == NULL)
	// 			return (NULL);
	// 		j = 0;
	// 		while (start <= end)
	// 		{
	// 			substring[j] = s[start];
	// 			j++;
	// 			start++;
	// 		}
// 			substring[j] = '\0';
// 			space[count] = substring;
// 			count++;
// 		}
// 	}
// 	space[count] = NULL;
// 	return (space);
// }

// int	main(void)
// {
// 	char	**res;
// 	int 	i;

// 	res = ft_split("Hallo my name is Sascha", ' ');
// 	i = 0;
// 	while (res && res[i])
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// 	return (0);
// }
