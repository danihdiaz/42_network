/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugarcia <lugarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:42:45 by lugarcia          #+#    #+#             */
/*   Updated: 2026/03/09 18:06:04 by lugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void ft_bubble_sort(t_stack **stack_a, int size)
{
	int i;
	int sorted;
	
	sorted = 0;
	while(!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < size - 1)
		{
			if ((*stack_a)->value > (*stack_a)->next->value)
			{
				sa(*stack_a);
				sorted = 0;
			}
			ra(stack_a);
			i++;
		}
		ra(stack_a);
	}
}


/*#include <stdlib.h>

t_stack *ft_stack_new(int value)
{
    t_stack *new;

    new = malloc(sizeof(t_stack));
    if (!new)
        return (NULL);
    new->value = value;
    new->index = 0;
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

    ft_lsadd_back(&stack_a, ft_stack_new(500));
    ft_lsadd_back(&stack_a, ft_stack_new(-10));
    ft_lsadd_back(&stack_a, ft_stack_new(100));
    ft_lsadd_back(&stack_a, ft_stack_new(0));
    ft_lsadd_back(&stack_a, ft_stack_new(42));
    ft_lsadd_back(&stack_a, ft_stack_new(43));
    ft_lsadd_back(&stack_a, ft_stack_new(44));

    
    printf("Estado inicial:\n");
    print_stack(stack_a);
	
	ft_bubble_sort(&stack_a, 7);
	
	printf("Estado final:\n");
    print_stack(stack_a);
    return (0);
}*/