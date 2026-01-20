/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-19 15:47:24 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-19 15:47:24 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;
    size_t i;

    i = 0;
    if (dest == src)
        return (dest);
    if (n == 0)
        return (dest);
    if (d < s)
    {
        while (i < n)
        {
            d[i] = s[i];
            i++;
        }
    }
    else if (s < d)
    {
        i = n - 1;    
        while (i > 0)
        {
            d[i] = s[i];
            i--;
        }
        if (i == 0)
            d[i] = s[i];
    }
    return (dest);
}