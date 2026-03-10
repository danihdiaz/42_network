/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_op_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:55:42 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/10 13:45:41 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	ft_rot_stack(t_stack **stack, int lst_sz, int pos)
{
	int	lst_pos;

	if (pos < (lst_sz / 2))
	{
		while (pos > 0)
		{
			rb(stack);
			pos--;
		}
	}
	else
	{
		lst_pos = lst_sz - pos;
		while (lst_pos > 0)
		{
			rrb(stack);
			lst_pos--;
		}
	}
}
