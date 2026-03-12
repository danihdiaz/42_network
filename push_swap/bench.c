/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:03:44 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/12 18:33:50 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_disorder(float disorder)
{
	int	integer;
	int	decimal;

	disorder *= 100;
	integer = (int)disorder;
	decimal = (int)((disorder - integer) * 100);
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(integer, 2);
	write(2, ".", 1);
	ft_putnbr_fd(decimal, 2);
	write(2, "%\n", 2);
}

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
	print_disorder(disorder);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putstr_fd(ft_get_name(strategy), 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(ft_get_complexity(strategy), 2);
	ft_putstr_fd("\n", 2);
	// ft_putstr_fd("[bench] total_ops: ", 2);
	// ft_putnbr_fd(total_ops, 2);
	// ft_putstr_fd("\n", 2);
}

