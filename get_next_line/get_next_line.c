/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:25:20 by doji              #+#    #+#             */
/*   Updated: 2024/04/13 18:19:36 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	if (!*remainder)
		return (NULL);

	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		line = ft_substr(*remainder, 0, newline_pos - *remainder + 1);
		temp = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = temp;
	}
	else
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}

	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];
	char		*buffer;
	char		*temp;
	ssize_t		bytes_read;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;

		buffer[bytes_read] = '\0';
		if (!remainder[fd])
			remainder[fd] = ft_strdup("");

		temp = ft_strjoin(remainder[fd], buffer);
		free(remainder[fd]);
		remainder[fd] = temp;

		if (ft_strchr(remainder[fd], '\n'))
			break ;
	}

	free(buffer);

	if (bytes_read < 0)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}

	return (extract_line(&remainder[fd]));
}
