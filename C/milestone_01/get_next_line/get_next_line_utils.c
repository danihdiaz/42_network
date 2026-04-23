/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:56:14 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/17 13:01:07 by dhontani         ###   ########.fr       */
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

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 1 + (stash[i] == '\n'));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_stash(char *stash, size_t *stash_len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
		return (free(stash), *stash_len = 0, NULL);
	j = 0;
	temp = malloc(*stash_len - i);
	if (!temp)
		return (free(stash), *stash_len = 0, NULL);
	j = 0;
	while (stash[i + 1 + j])
	{
		temp[j] = stash[i + 1 + j];
		j++;
	}
	temp[j] = '\0';
	*stash_len = j;
	return (free(stash), temp);
}

char	*stash_join(char *stash, char *buffer, size_t *stash_len)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!buffer)
		return (stash);
	if (!stash)
		tmp = malloc(ft_strlen(buffer) + 1);
	else
		tmp = malloc(*stash_len + ft_strlen(buffer) + 1);
	if (!tmp)
		return (free(stash), *stash_len = 0, NULL);
	while (i < *stash_len)
	{
		tmp[i] = stash[i];
		i++;
	}
	while (buffer[j])
		tmp[i++] = buffer[j++];
	tmp[i] = '\0';
	*stash_len = i;
	return (free(stash), tmp);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
