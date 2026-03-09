/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-23 13:31:24 by dhontani          #+#    #+#             */
/*   Updated: 2026-02-23 13:31:24 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack, char *op)
{
	int	tmp;

	if (!stack || !stack->next)
		return ;
	tmp = stack->value;
	stack->value = stack->next->value;
	stack->next->value = tmp;
	if (op[0])
		ft_printf("%s\n", op);
}

void	sa(t_stack *stack)
{
	swap(stack, "sa");
}

void	sb(t_stack *stack)
{
	swap(stack, "sb");
}

void	ss(t_stack *a, t_stack *b)
{
	swap(a, "");
	swap(b, "");
	ft_printf("ss\n");
}
