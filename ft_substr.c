/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-21 15:11:30 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-21 15:11:30 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t i;
    unsigned const char *s1;
    unsigned char *p;

    s1 = (unsigned char *)s;
    i = 0;

    p = malloc(len);
    while (s1[i] && i != start)
        i++;
    if (i == start)
        while (s[i] && i < len)
            i++;
    

}