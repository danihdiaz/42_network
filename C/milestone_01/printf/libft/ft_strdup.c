/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:27:58 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/26 12:22:18 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	const unsigned char	*s1;
	size_t				i;
	size_t				j;
	char				*dup;

	s1 = (const unsigned char *)s;
	i = 0;
	j = 0;
	while (s1[i])
	{
		i++;
	}
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	while (j <= i)
	{
		dup[j] = s1[j];
		j++;
	}
	return (dup);
}
