/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:03:17 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/18 19:07:03 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t  ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t	i;
    size_t  j;
    size_t  k;
    size_t  disp;
    
    i = 0;
    j = 0;
    k = 0;
    
    if (dstsize == 0)
    {    
        return (ft_strlen(src));
    }    
    while (dst[i] && i < dstsize)
        i++;
    if (i == dstsize)
        return (dstsize + ft_strlen(src));
    disp = dstsize - i - 1;
    if (disp == 0)
        return (i + ft_strlen(src));
    while (src[j] && j < disp)
        j++;
    while (src[k] && k < j)
    {    
        dst[i] = src[k];
        i++;
        k++;
    }
    dst[i] = '\0';
    return (i);
}

