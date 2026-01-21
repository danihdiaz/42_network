/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-20 17:16:51 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-20 17:16:51 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

void *ft_calloc(size_t nmemb, size_t size)
{
    void *mem;

    if (size != 0 && nmemb > SIZE_MAX / size)
        return (NULL);
    mem = malloc(nmemb * size);
    if (!mem)
        return (NULL);
    ft_bzero(mem, nmemb * size);
    return (mem);
}
/*
int main(void)
{
    int *s;
    int i;

    i = 0;
    s = ft_calloc(5, sizeof(int));
    while (i < 5)
    {
        printf("%d", s[i]);
        i++;
    }

    free(s);
    s = NULL;
}
*/