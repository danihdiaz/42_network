/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-16 14:51:41 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-16 14:51:41 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strlcpy(char *dst,const char *src, size_t dstsize)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;

    if (dstsize == 0)
    {
        while (src[j] != '\0')
            j++;
        return (j);
    }
    while (i < dstsize - 1 && src[j] != '\0')
    {    
        dst[i] = src[j];
        i++;
        j++;
    }
    if (dstsize > 0)
        dst[i] = '\0';
    while (src[j] != '\0')
        j++;
    return (j);
}