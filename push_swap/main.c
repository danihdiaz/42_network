/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 11:26:33 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/12 18:34:16 by dhontani         ###   ########.fr       */
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
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		strategy;
	int		bench;
	float	disorder;

	stack_a = NULL;
	stack_b = NULL;
	strategy = ADAPTIVE;
	bench = 0;
	if (argc < 2)
		return (0);
	stack_a = ft_parse_input(argc, argv, &strategy, &bench);
	if (!stack_a)
		return (1);
	set_index(stack_a);
	if (bench)
		disorder = compute_disorders(stack_a);
	// if (strategy == SIMPLE)
	// 	simple_alg(&stack_a, &stack_b);
	else if (strategy == MEDIUM)
		med_alg(&stack_a, &stack_b);
	// else if (strategy == COMPLEX)
	// 	complex_alg(&stack_a, &stack_b);
	else
		adaptive_alg(&stack_a, &stack_b, compute_disorders(stack_a));
	if (bench)
		print_bench(disorder, strategy);
	return (0);
}
