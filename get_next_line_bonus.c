/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndi-tull <ndi-tull@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:13:36 by ndi-tull          #+#    #+#             */
/*   Updated: 2025/11/29 11:28:36 by ndi-tull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	len = i;
	if (stash[i] == '\n')
		len = i + 1;
	line = ft_substr(stash, 0, len);
	free(stash);
	return (line);
}

static void	clean_stash(char *line)
{
	size_t	i;
	size_t	count;

	count = 0;
	if (!line)
		return ;
	i = 0;
	while (line[count] && line[count] != '\n')
		count++;
	if (line[count] == '\n')
		count++;
	while (line[count])
	{
		line[i] = line[count];
		i++;
		count++;
	}
	line[i] = 0;
}

char	*checkbytes(char *line)
{
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1] = {0};
	ssize_t		bytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		buffer[fd][0] = 0;
		return (NULL);
	}
	bytes = 1;
	line = ft_strdup(buffer[fd]);
	while (line && !ft_strchr(buffer[fd], '\n') && bytes > 0)
	{
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes < 0)
			return (checkbytes(line));
		buffer[fd][bytes] = '\0';
		line = ft_strjoin(line, buffer[fd]);
	}
	if (line)
		line = extract_line(line);
	clean_stash(buffer[fd]);
	return (line);
}
