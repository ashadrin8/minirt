/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:20:51 by ashadrin          #+#    #+#             */
/*   Updated: 2025/08/20 16:06:07 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffers[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffers[fd] = read_and_stash(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = the_line(buffers[fd]);
	if (!line)
		return (free(buffers[fd]), buffers[fd] = NULL, NULL);
	buffers[fd] = updated_stash(buffers[fd]);
	if (buffers[fd] && !buffers[fd][0])
		return (free(buffers[fd]), buffers[fd] = NULL, line);
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

// int main ()
// {
// 	int fd1;
// 	int fd2;
// 	char *line1;
// 	char *line2;

// 	fd1 = open("text1.txt", O_RDONLY);
// 	fd2 = open("text2.txt", O_RDONLY);

// 	if(fd1 < 0 || fd2 < 0)
// 		return (printf("couldn't read from the files\n"), 1);
// 	//0 - success, 1 - general error, 2 - file not found, 3 - invalid input
// 	line1 = get_next_line(fd1);
// 	line2 = get_next_line(fd2);
// 	while (line1 || line2)
// 	{
// 		if (line1)
// 		{
// 			printf("%s", line1);
// 			free(line1);
// 			line1 = get_next_line(fd1);
// 		}
// 		if (line2)
// 		{
// 			printf("%s", line2);
// 			free(line2);
// 			line2 = get_next_line(fd2);
// 		}
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }
