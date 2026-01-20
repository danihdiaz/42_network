/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-20 10:26:52 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-20 10:26:52 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    unsigned char *s = (unsigned char *)s1;
    unsigned char *d = (unsigned char *)s2;
    size_t i;
    int res;

    i = 0;
    while (i < n)
    {
        if (s[i] != d[i])
            return (s[i] - d[i]);
        i++;
    }
    return (0);
}