/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-27 11:14:31 by dhontani          #+#    #+#             */
/*   Updated: 2026-01-27 11:14:31 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(long n)
{
	size_t	d;

	d = 1;
	while (n >= 10)
	{
		n /= 10;
		d++;
	}
	return (d);
}

char	*ft_itoa(int n)
{
	long	num;
	size_t	len;
	char	*s;

	num = n;
	len = (num < 0);
	if (num < 0)
		num = -num;
	len = len + count_digits(num);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (len--)
	{
		s[len] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}
