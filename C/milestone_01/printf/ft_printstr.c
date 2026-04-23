/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:20:54 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/05 14:46:45 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *c)
{
	if (!c)
		return (write(1, "(null)", 6));
	ft_putstr_fd(c, 1);
	return (ft_strlen(c));
}
