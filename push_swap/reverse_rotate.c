/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:48:53 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/24 13:59:14 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack **stack, char *op)
{
	t_stack	*current;
	t_stack	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	current = *stack;
	while (current->next->next != NULL)
		current = current->next;
	tmp = ft_lstlast(*stack);
	current->next = NULL;
	tmp->next = *stack;
	*stack = tmp;
	if (op[0])
		printf("%s", op);
}

void	rra(t_stack **stack_a)
{
	reverse_rotate(stack_a, "rra\n");
}

void	rrb(t_stack **stack_b)
{
	reverse_rotate(stack_b, "rrb\n");
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	reverse_rotate(stack_a, "");
	reverse_rotate(stack_b, "");
	printf("rrr\n");
}