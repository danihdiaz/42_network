/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:03:17 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/17 13:30:19 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t  ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t	i;
    size_t  j;
    size_t  len;
    
    i = 0;
    j = 0;
    
    if (dstsize == 0)
    {    
        return (ft_strlen(src));
    }    
	
    while (dst[i])
        i++;
    while (src[j] <= dstsize - 1 && src[j] != '\0')
    {    
        dst[i] = src[j];
        i++;
        j++;
    }       
    return (i);
}

