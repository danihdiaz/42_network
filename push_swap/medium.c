/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-05 10:48:51 by dhontani          #+#    #+#             */
/*   Updated: 2026-03-05 10:48:51 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	med_alg(t_stack *stack_a, t_stack *stack_b)
{
	int	numbrs;
	int	chnks;
	int	chnk_sz;
	int	crnt_chnk;
	int	i;
	int	index;
	int	pos;

	numbrs = ft_listsize(stack_a);
	chnks = ft_sqrt_int(numbrs);
	chnk_sz = ft_ceil_div(numbrs, chnks);
	crnt_chnk = chnks;

	while (crnt_chnk > 0)
	{
		i = 0;
		while (i < chnk_sz)
		{
			if (get_chunk(chnk_sz, stack_a->index) == crnt_chnk)
			{
				pb(&stack_a, &stack_b);
				i++;
			}
			else
				ra(&stack_a);
		}
		crnt_chnk--;
	}
	index = chnk_sz - 1;
	while (index >= 0)
	{
		pos = ft_find_pos(&stack_a, index);
		ft_rot_stack(&stack_a, ft_listsize(stack_a), pos, 'a');
		index--;
	}
	index = numbrs - 1;
	while (index >= chnk_sz)
	{
		ft_pck_op(&stack_a, &stack_b, ft_listsize(stack_b), index);
		index--;
	}
}
