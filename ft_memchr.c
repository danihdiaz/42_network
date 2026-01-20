/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-20 10:13:56 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-20 10:13:56 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
    unsigned char *s1 = (unsigned char *)s;
    unsigned char c1 = (unsigned char)c;
    size_t i;

    i = 0;
    while (i < n)
    {
        if (s1[i] == c1)
            return (&s1[i]);
        i++;
    }
    return (NULL);
}