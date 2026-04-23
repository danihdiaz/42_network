/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:48:51 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/10 18:38:14 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_chunks(t_stack **stack_a, t_stack **stack_b, int chksz, int chnks)
{
	int	i;
	int	size;

	size = ft_listsize(*stack_a);
	i = 0;
	while (i < chksz && size > 0)
	{
		if (get_chunk(chksz, (*stack_a)->index) == chnks)
		{
			pb(stack_a, stack_b);
			i++;
		}
		else
		{
			ra(stack_a);
			size--;
		}
	}
}

void	med_alg(t_stack **stack_a, t_stack **stack_b)
{
	int	numbrs;
	int	chnks;
	int	chnk_sz;

	numbrs = ft_listsize(*stack_a);
	chnks = ft_sqrt_int(numbrs);
	chnk_sz = ft_ceil_div(numbrs, chnks);

	while (chnks >= 0)
		push_chunks(stack_a, stack_b, chnk_sz, chnks--);
	chnks = numbrs - 1;
	while (chnks >= 0)
		ft_pck_op(stack_a, stack_b, ft_listsize(*stack_b), chnks--);
}
