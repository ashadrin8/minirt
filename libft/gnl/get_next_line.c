/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:26:52 by ashadrin          #+#    #+#             */
/*   Updated: 2025/08/20 18:35:38 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_stash(fd, buffer);
	if (!buffer)
		return (NULL);
	line = the_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = updated_stash(buffer);
	if (buffer && !buffer[0])
		return (free(buffer), buffer = NULL, line);
	return (line);
}

char	*read_and_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			if (stash)
				free(stash);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		if (temp)
			free(temp);
	}
	return (stash);
}

char	*the_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i += 1;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		return (line[i] = stash[i], i++, line[i] = '\0', line);
	return (line[i] = '\0', line);
}

char	*updated_stash(char *stash)
{
	int		counter;
	int		rem_counter;
	char	*remainder;

	counter = 0;
	rem_counter = 0;
	while (stash[counter] != '\n' && stash[counter])
		counter++;
	if (!stash[counter])
		return (free(stash), NULL);
	counter++;
	if (!stash[counter])
		return (free(stash), NULL);
	remainder = malloc(ft_strlen(stash + counter) + 1);
	if (!remainder)
		return (free(stash), NULL);
	while (stash[counter + rem_counter] != '\0')
	{
		remainder[rem_counter] = stash[counter + rem_counter];
		rem_counter++;
	}
	remainder[rem_counter] = '\0';
	free(stash);
	return (remainder);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (printf("this thing's unreadable\n"), -1);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
