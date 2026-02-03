/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-03 12:03:06 by dhontani          #+#    #+#             */
/*   Updated: 2026-02-03 12:03:06 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	formatreat(char c)
{

}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	vargs;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += formatreat(format[i + 1]);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			count += 1;
		}
		i++;
	}
	return (count);
}
