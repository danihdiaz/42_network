/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printvoid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:36:19 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/05 15:29:06 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printvoid(void *p)
{
	uintptr_t	n;

	n = (uintptr_t)p;
	if (!n)
		return (ft_printstr("(nil)"));
	ft_printstr("0x");
	return (ft_puthex_base(n, 0) + 2);
}
