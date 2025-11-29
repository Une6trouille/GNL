/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndi-tull <ndi-tull@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:32:04 by ndi-tull          #+#    #+#             */
/*   Updated: 2025/11/29 11:25:56 by ndi-tull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static void	clean_buffer(char *line)
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
	static char	buffer[BUFFER_SIZE + 1] = {0};
	ssize_t		bytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		buffer[0] = 0;
		return (NULL);
	}
	bytes = 1;
	line = ft_strdup(buffer);
	while (line && !ft_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (checkbytes(line));
		buffer[bytes] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (line)
		line = extract_line(line);
	clean_buffer(buffer);
	return (line);
}
