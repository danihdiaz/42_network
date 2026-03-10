/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:48:14 by lugarcia          #+#    #+#             */
/*   Updated: 2026/03/10 14:13:40 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <string.h>

void	free_splt(char **splt)
{
	int	k;

	k = 0;
	while (splt[k])
		k++;
	while (k > 0)
		free(splt[--k]);
	free(splt);
}

void	ft_lstad_back(t_stack **lst, t_stack *new)
{
	t_stack	*i;

	if (!lst || !new)
		return ;
	i = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (i->next != NULL)
		i = i->next;
	i->next = new;
}

t_stack	*ft_new_node(int num)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->value = num;
	new->next = NULL;
	return (new);
}

void	print_stacks(t_stack *a, t_stack *b)
{
	printf("Pila A: ");
	while (a)
	{
		printf("%d ", a->value);
		a = a->next;
	}
	printf("\nPila B: ");
	while (b)
	{
		printf("%d ", b->value);
		b = b->next;
	}
	printf("\n-----------------\n");
}

t_stack	*ft_parse_input(int argc, char **argv)
{
	size_t	offset;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_b = NULL;
	offset = ft_find_flags(argc, argv);
	if (!ft_check_args(offset, argv))
		return (write(2, "error\n", 6), NULL);
	stack_a = ft_stack_init(offset, argv);
	if (!stack_a)
		return (write(2, "error\n", 6), NULL);
	print_stacks(stack_a, stack_b);
	return (stack_a);
}
/*static void	print_stacks(t_stack *a)
{
	printf("Pila A: ");
	while (a)
	{
		printf("%d ", a->value);
		a = a->next;
	}
	printf("\n-----------------\n");
}
*/