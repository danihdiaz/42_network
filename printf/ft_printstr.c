/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-03 16:20:54 by dhontani          #+#    #+#             */
/*   Updated: 2026-02-03 16:20:54 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_printstr(va_list vargs)
{
	char	*c;

	c = va_arg(vargs, char *);
	ft_putstr_fd(c, 1);
	return (ft_strlen(c));
}
