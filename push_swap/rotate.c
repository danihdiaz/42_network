/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:22:52 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/24 13:43:38 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **stack, char *op)
{
	t_stack	*tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	ft_lstlast(*stack)->next = tmp;
	tmp->next = NULL;
	if (op[0])
		printf("%s", op);
}

void	ra(t_stack **stack_a)
{
	rotate(stack_a, "ra\n");
}

void	rb(t_stack **stack_b)
{
	rotate(stack_b, "rb\n");
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a, "");
	rotate(stack_b, "");
	printf("rr\n");
}
