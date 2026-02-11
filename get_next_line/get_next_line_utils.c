/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:56:14 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/11 20:29:43 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(char *stash)
{
	size_t	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc (i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_stash(char *stash)
{
	size_t	i;
	size_t	size;
	char	*temp;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	size = strlen(stash + i + 1);
	temp = malloc(size + 1);
	if (!temp)
		return (NULL);
	size = 0;
	while (stash[i + 1 + size])
	{
		temp[size] = stash[i + 1 + size];
		size++;
	}
	temp[size] = '\0';
	free(stash);
	return (temp);
}

char	*stash_join(char *buffer, char *stash)
{
	size_t	i;
	char	*temp;
	size_t	k;
	size_t	len_stash;

	i = 0;
	if (!stash)
		len_stash = 0;
	else
		len_stash = strlen(stash);
	temp = malloc(len_stash + (strlen(buffer)) + 1);
	if (!temp)
		return (NULL);
	if (stash)
	{
		while (stash[i])
			temp[i] = stash[i++];
	}
	k = 0;
	while (buffer[k])
		temp[i++] = buffer[k++];
	temp[i] = '\0';
	free(stash);
	return (temp);
}

char	*free_all(char *buffer, char *stash)
{
	free(buffer);
	free(stash);
	return (NULL);
}
