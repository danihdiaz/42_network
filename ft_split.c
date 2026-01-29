/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:06:07 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/29 20:23:24 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **wrds, int k)
{
	while (k > 0)
		free(wrds[--k]);
	free(wrds);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	wrd;

	i = 0;
	wrd = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			wrd++;
		i++;
	}
	return (wrd);
}

static int	fill_words(char **wrds, char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	start;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			wrds[k] = ft_substr(s, start, i - start);
			if (!wrds[k])
				return (free_all(wrds, k), 0);
			k++;
		}
		else
			i++;
	}
	wrds[k] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**wrds;

	if (!s)
		return (NULL);
	wrds = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!wrds)
		return (NULL);
	if (!fill_words(wrds, s, c))
		return (NULL);
	return (wrds);
}
