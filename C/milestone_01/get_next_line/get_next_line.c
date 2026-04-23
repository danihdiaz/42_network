/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:07:06 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/17 12:49:10 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	cleanup_and_reset(char **stash, size_t *stash_len)
{
	free(*stash);
	*stash = NULL;
	*stash_len = 0;
}

static int	read_to_stash(int fd, char **stash, size_t *stash_len, char *buffer)
{
	int	n;

	n = 1;
	while (!has_newline(*stash) && n != 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
			return (cleanup_and_reset(stash, stash_len), -1);
		if (n > 0)
		{
			buffer[n] = '\0';
			*stash = stash_join(*stash, buffer, stash_len);
			if (!*stash)
				return (*stash_len = 0, -1);
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	static size_t	stash_len;
	char			*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (cleanup_and_reset(&stash, &stash_len), NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (stash)
			cleanup_and_reset(&stash, &stash_len);
		return (NULL);
	}
	if (read_to_stash(fd, &stash, &stash_len, buffer) == -1)
		return (free(buffer), NULL);
	line = extract_line(stash);
	if (!line)
	{
		if (stash)
			cleanup_and_reset(&stash, &stash_len);
		return (free(buffer), NULL);
	}
	stash = update_stash(stash, &stash_len);
	return (free(buffer), line);
}
