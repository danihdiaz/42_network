/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:03:06 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/05 15:41:21 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	formatreat(char c, va_list vargs)
{
	if (c == 'c')
		return (ft_printchar(va_arg(vargs, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(vargs, char *)));
	else if (c == 'p')
		return (ft_printvoid(va_arg(vargs, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_printint(va_arg(vargs, int)));
	else if (c == 'u')
		return (ft_printunint(va_arg(vargs, unsigned int)));
	else if (c == 'x')
		return (ft_printhex_x(va_arg(vargs, unsigned int)));
	else if (c == 'X')
		return (ft_printhex_up(va_arg(vargs, unsigned int)));
	else if (c == '%')
		return (write(1, &c, 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	vargs;

	va_start(vargs, format);
	i = 0;
	count = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += formatreat(format[i + 1], vargs);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			count += 1;
		}
		i++;
	}
	va_end(vargs);
	return (count);
}
