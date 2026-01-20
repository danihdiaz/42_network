/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-20 10:45:20 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-20 10:45:20 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_atoi(const char *nptr)
{
    int i;
    int num;
    int res;
    int sign;

    i = 0;
    res = 0;
    sign = 1;
    while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
        i++;
    if (nptr[i] == 43)
        i++;
    if (nptr[i] == 45)
    {  
        sign = -sign;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        num = nptr[i] - '0';
        res = res * 10 + num;
        i++;
    }
    return (res * sign);
}