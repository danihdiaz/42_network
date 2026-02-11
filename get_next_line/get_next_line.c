/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:07:06 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/11 20:15:09 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	int			n;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFF_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!has_newline(stash))
	{
		n = read(fd, buffer, BUFF_SIZE);
		if (n == -1)
			return (free_all(buffer, stash));
		if (n == 0)
			break ;
		buffer[n] = '\0';
		stash = stash_join(buffer, stash);
	}
	if (!stash)
		return (free_all(buffer, NULL));
	line = extract_line(stash);
	stash = update_stash(stash);
	return (free(buffer), line);
}
