/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printvoid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-03 16:36:19 by dhontani          #+#    #+#             */
/*   Updated: 2026-02-03 16:36:19 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_printvoid(va_list vargs)
{
	void		*c;
	uintptr_t	z;

	c = va_arg(vargs, void *);
	z = (uintptr_t)c;

}
