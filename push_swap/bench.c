/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:44 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/11 19:10:11 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*ft_get_name(int strategy)
{
	if (strategy == SIMPLE)
		return ("Simple");
	if (strategy == MEDIUM)
		return ("Medium");
	if (strategy == COMPLEX)
		return ("Complex");
	return ("Adaptive");
}

static char	*ft_get_complexity(int strategy)
{
	if (strategy == SIMPLE)
		return ("O(n^2)");
	if (strategy == MEDIUM)
		return ("O(n*sqrt(n))");
	if (strategy == COMPLEX)
		return ("O(n log n)");
	return ("Adaptive");
}

void	print_bench(float disorder, int strategy)
{
	ft_printf_fd(2, "[bench] disorder: %.2f%%\n", disorder * 100);
	ft_printf_fd(2, "[bench] strategy: %s / ", ft_get_name(strategy));
	ft_printf_fd(2, "%s\n", ft_get_complexity(strategy));
}
