/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 11:26:33 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/10 19:13:17 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int	main(int argc, char **argv)
// {
// 	t_stack	*stack_a;
// 	t_stack	*stack_b;

// 	stack_a = NULL;
// 	stack_b = NULL;
// 	stack_a = ft_parse_input(argc, argv);

// 	printf("Estado inicial:\n");
// 	print_stacks(stack_a, stack_b);

// 	printf("Ejecutando pb o pa...\n");
// 	print_stacks(stack_a, stack_b);

// 	printf("Ejecutando pb o pa otra vez...\n");
// 	print_stacks(stack_a, stack_b);
// 	set_index(stack_a);
// 	while (stack_a)
// 	{
// 		printf("valor: %d\níndice: %d\n\n", stack_a->value, stack_a->index);
// 		stack_a = stack_a->next;
// 	}
// 	return (0);
// }

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	stack_a = ft_parse_input(argc, argv);
	set_index(stack_a);
	printf("Estado inicial:\n");
	print_stacks(stack_a, stack_b);
	med_alg(&stack_a, &stack_b);
	printf("Estado final:\n");
	print_stacks(stack_a, stack_b);
	return (0);
}
