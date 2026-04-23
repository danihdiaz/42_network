/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disorder_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugarcia <lugarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:36:40 by lugarcia          #+#    #+#             */
/*   Updated: 2026/03/02 17:09:48 by lugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	ft_siguiente(t_stack *stack_a, double total_comb)
{
	t_stack	*i;
	t_stack	*j;
	float	mistakes;

	i = stack_a;
	mistakes = 0;
	while (i->next != NULL)
	{
		j = i->next;
		while (j->next != NULL)
		{
			if (j->value < i->value)
				mistakes++;
			j = j->next;
		}
		if (j->value < i->value)
			mistakes++;
		i = i->next;
	}
	return (mistakes / total_comb);
}

float	compute_disorders(t_stack *stack_a)
{
	float	total_comb;
	int		n;
	t_stack	*i;

	if (!stack_a || !stack_a->next)
		return (0);
	total_comb = 0;
	i = stack_a;
	n = 1;
	while (i->next != NULL)
	{
		i = i->next;
		n++;
	}
	total_comb = n * (n - 1) / 2;
	return (ft_siguiente(stack_a, total_comb));
}

/*
#include <stdlib.h>

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

void print_stacks(t_stack *a, t_stack *b)
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

int main(void)
{
    t_stack *stack_a = NULL;
    t_stack *stack_b = NULL;

    ft_lsadd_back(&stack_a, ft_stack_new(2));
    ft_lsadd_back(&stack_a, ft_stack_new(3));
    ft_lsadd_back(&stack_a, ft_stack_new(1));
    
    printf("Estado inicial:\n");
    print_stacks(stack_a, stack_b);

    printf("Indice de errores...\n");
	printf("%f\n", compute_disorders(stack_a));

    return (0);
}*/