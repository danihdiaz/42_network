/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-25 12:08:44 by dhontani          #+#    #+#             */
/*   Updated: 2026-02-25 12:08:44 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_check_sign(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i = 1;
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_has_only_digits(char *str, int start)
{
	if (!str[start])
		return (0);
	while (str[start])
	{
		if (str[start] < '0' || str[start] > '9')
			return (0);
		start++;
	}
	return (1);
}

int	ft_is_valid_number(char *str)
{
	int	start;

	if (!str || !str[0])
		return (0);
	start = 0;
	if (str[0] == '+' || str[0] == '-')
		start = 1;
	if (!ft_check_sign(str))
		return (0);
	if (!ft_has_only_digits(str, start))
		return (0);
	return (1);
}
