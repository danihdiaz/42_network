/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:07:06 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/19 21:04:09 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	cleanup_and_reset(char **stash)
{
	free(*stash);
	*stash = NULL;
}

static int	read_to_stash(int fd, char **stash, char *buffer)
{
	int	n;

	n = 1;
	while (!has_newline(*stash) && n != 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
			return (cleanup_and_reset(stash), -1);
		if (n > 0)
		{
			buffer[n] = '\0';
			*stash = stash_join(*stash, buffer);
			if (!*stash)
				return (-1);
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*stash[MAX_FD];
	char			*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (stash[fd])
			cleanup_and_reset(&stash[fd]);
		return (NULL);
	}
	if (read_to_stash(fd, &stash[fd], buffer) == -1)
		return (free(buffer), NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		if (stash[fd])
			cleanup_and_reset(&stash[fd]);
		return (free(buffer), NULL);
	}
	stash[fd] = update_stash(stash[fd]);
	return (free(buffer), line);
}
