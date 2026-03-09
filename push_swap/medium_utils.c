/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-09 11:38:28 by dhontani          #+#    #+#             */
/*   Updated: 2026-03-09 11:38:28 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_pck_op(t_stack **stack_a, t_stack **stack_b, int lst_sz, int index)
{
	int	pos;

	pos = ft_find_pos(stack_b, index);
	ft_rot_stack(stack_b, lst_sz, pos, 'b');
	pa(stack_a, stack_b);
}

int	ft_listsize(t_stack *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_sqrt_int(int n)
{
	int	i;

	i = 0;
	while (i * i != n)
	{
		if (i * i > n)
			break ;
		i++;
	}
	return (i);
}

int	ft_ceil_div(int n, int i)
{
	if (n % i != 0)
		return (n / i + 1);
	return (n / i);
}

int	get_chunk(int chunk_size, int index)
{
	return (index / chunk_size);
}
