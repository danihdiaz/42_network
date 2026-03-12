/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:31:24 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/12 18:31:54 by dhontani         ###   ########.fr       */
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
		printf("%s\n", op);
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
	printf("ss\n");
}
