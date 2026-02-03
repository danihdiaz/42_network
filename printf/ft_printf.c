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

static int	formatreat(char c, va_list vargs)
{
	if (c == 'c')
		return (ft_printchar(vargs));
	else if (c == 's')
		return (ft_printstr(vargs));
	else if (c == 'p')
		return (ft_printvoid(vargs));
	else if (c == 'd')
		return (ft_imprimir numero decimal base 10);
	else if (c == 'i')
		return ("" entero base 10)
	else if (c == 'u')
		return ("" nº decimal base 10 sinsigno);
	else if (c == 'x')
		return (hexaenminusculas)
	else if (c == 'X')
		return (hexamayusculas)
	else if (c == '%')
		write(1, &c, 1);
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
	while (format[i])
	{
		if (format[i] == '%')
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
