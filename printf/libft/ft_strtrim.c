/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:22:00 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/26 13:31:54 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	findlimits(char const *s1, char const *set,
						size_t *start, size_t *end)
{
	size_t	len;

	len = ft_strlen(s1);
	*start = 0;
	while (s1[*start] && ft_strchr(set, s1[*start]))
		(*start)++;
	if (len == 0)
	{
		*end = 0;
		return ;
	}
	*end = len - 1;
	while (*end > *start && ft_strchr(set, s1[*end]))
		(*end)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	findlimits(s1, set, &start, &end);
	if (start > end)
		return (ft_strdup(""));
	res = malloc(end - start + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (start <= end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}
