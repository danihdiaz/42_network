/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:19:06 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/24 18:34:33 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}
/*
int main(void)
{
    char s[] = "hola";
    int i;

    i = 0;
    ft_bzero(s, 5);
    while (i < 5)
    {
        printf("%d", s[i]);
        i++;
    }
}
*/