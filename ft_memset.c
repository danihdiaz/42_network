/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-19 14:53:55 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-19 14:53:55 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void *ft_memset(void  *s, int c, size_t n)
{
    unsigned char *s1 = (unsigned char *)s;
    unsigned char c1 = (unsigned char)c;
    size_t i;

    i = 0;
    while (i < n)
    {
        s1[i] = c1;
        i++;
    }
    return (s);
}