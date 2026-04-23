/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugarcia <lugarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:53:07 by lugarcia          #+#    #+#             */
/*   Updated: 2026/03/09 18:23:42 by lugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->index > stack->next->index)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int count_bits(int size)
{
    int k;

	k = 0;
    while ((1 << k) < size)
    {
        k++;
    }
    return (k);
}

void	radix_sort(t_stack **stack_a, t_stack **stack_b, int size)
{
	int	k;
	int	i;
	int j;

	k = count_bits(size);
	i = 0;
	while (i < k)
	{
		j = 0;
		while (j < size)
		{
			if ((((*stack_a)->index >> i) & 1) == 0)
			{
				pb(stack_a, stack_b);
			}
			else if ((((*stack_a)->index >> i) & 1) == 1)
			{
				ra(stack_a);
			}
			j++;
		}
		while ((*stack_b))
		{
			pa(stack_a, stack_b);
		}
		if (is_sorted(*stack_a))
			break;
		i++;
	}
}

/*
#include <stdlib.h>

void free_stack(t_stack **stack)
{
    t_stack *tmp;
    while (*stack)
    {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
}

void ft_index_stack(t_stack *stack)
{
    t_stack *current;
    t_stack *min_node;
    int     min_val;
    int     i;
    int     stack_size;

    stack_size = 0;
    current = stack;
    while (current && ++stack_size)
        current = current->next;

    i = 0;
    while (i < stack_size)
    {
        current = stack;
        min_node = NULL;
        min_val = 2147483647; 

        while (current)
        {
            if (current->value <= min_val && current->index == -1)
            {
                min_val = current->value;
                min_node = current;
            }
            current = current->next;
        }
        if (min_node)
            min_node->index = i++;
    }
}

t_stack *ft_stack_new(int value)
{
    t_stack *new = malloc(sizeof(t_stack));
    if (!new)
        return (NULL);
    new->value = value;
    new->index = -1;
    new->next = NULL;
    return (new);
}

t_stack *ft_lslast(t_stack *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void ft_lsadd_back(t_stack **lst, t_stack *new)
{
    t_stack *tmp;

    if (!lst || !new)
        return ;
    if (!*lst)
        *lst = new;
    else
    {
        tmp = ft_lslast(*lst);
        tmp->next = new;
    }
}

void print_stack(t_stack *a)
{
    printf("Pila A: ");
    while (a)
    {
        printf("%d ", a->value);
        a = a->next;
    }
    printf("\n-----------------\n");
}

int main(void)
{
    t_stack *stack_a = NULL;
    t_stack *stack_b = NULL;

    ft_lsadd_back(&stack_a, ft_stack_new(500));
    ft_lsadd_back(&stack_a, ft_stack_new(-10));
    ft_lsadd_back(&stack_a, ft_stack_new(100));
    ft_lsadd_back(&stack_a, ft_stack_new(0));
    ft_lsadd_back(&stack_a, ft_stack_new(42));
    ft_lsadd_back(&stack_a, ft_stack_new(43));
    ft_lsadd_back(&stack_a, ft_stack_new(44));

    ft_index_stack(stack_a);
    
    printf("\nEstado inicial (Valor [Índice]):\n");
    t_stack *tmp = stack_a;
    while (tmp) {
        printf("%d [%d] -> ", tmp->value, tmp->index);
        tmp = tmp->next;
    }
    printf("NULL\n\n");

    radix_sort(&stack_a, &stack_b, 7);

	printf("\nEstado final:\n");
	print_stack(stack_a);
	print_stack(stack_b);
    
    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}*/