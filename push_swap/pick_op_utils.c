/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_op_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-09 15:55:42 by dhontani          #+#    #+#             */
/*   Updated: 2026-03-09 15:55:42 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rot_up(t_stack **stack, char ab)
{
	if (ab == 'a')
		ra(stack);
	else
		rb(stack);
}

void	rot_down(t_stack **stack, char ab)
{
	if (ab == 'a')
		rra(stack);
	else
		rrb(stack);
}

int	ft_find_pos(t_stack **stack, int index)
{
	int		ind_pos;
	t_stack	*aux;

	ind_pos = 0;
	aux = *stack;
	while (aux)
	{
		if (aux->index == index)
			break ;
		ind_pos++;
		aux = aux->next;
	}
	return (ind_pos);
}

void	ft_rot_stack(t_stack **stack, int lst_sz, int pos, char ab)
{
	int	lst_pos;

	if (pos < (lst_sz / 2))
	{
		while (pos > 0)
		{
			rot_up(stack, ab);
			pos--;
		}
	}
	else
	{
		lst_pos = lst_sz - pos;
		while (lst_pos > 0)
		{
			rot_down(stack, ab);
			lst_pos--;
		}
	}
}
