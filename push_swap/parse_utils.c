/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-03 13:16:10 by dhontani          #+#    #+#             */
/*   Updated: 2026-03-03 13:16:10 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ft_find_flags(int argc, char **argv)
{
	size_t	i;

	i = 1;
	while (i < (size_t)argc && (!ft_strncmp(argv[i], "--simple", 11)
			|| !ft_strncmp(argv[i], "--medium", 11)
			|| !ft_strncmp(argv[i], "--complex", 11)
			|| !ft_strncmp(argv[i], "--adaptive", 11)))
		i++;
	return (i);
}

t_stack	*ft_stack_init(int offset, char **argv)
{
	int		j;
	int		num;
	char	**splt;
	t_stack	*stack_a;
	t_stack	*nodo;

	stack_a = NULL;
	while (argv[offset])
	{
		splt = ft_split(argv[offset], ' ');
		j = 0;
		while (splt[j] != NULL)
		{
			num = ft_atoi(splt[j]);
			nodo = ft_new_node(num);
			ft_lstad_back(&stack_a, nodo);
			j++;
		}
		free_splt(splt);
		offset++;
	}
	return (stack_a);
}

size_t	count_nodes(t_stack *stack_a)
{
	size_t	nodes;

	nodes = 1;
	while (stack_a->next)
	{
		nodes++;
		stack_a = stack_a->next;
	}
	return (nodes);
}

void	set_index(t_stack *stack_a)
{
	t_stack	*head;
	t_stack	*tail;
	size_t	i;
	size_t	nodes;

	nodes = count_nodes(stack_a);
	tail = stack_a;
	i = 0;
	while (i < nodes)
	{
		head = tail;
		stack_a->index = 0;
		while (head->next)
		{
			if (stack_a->value > head->value)
				stack_a->index++;
			head = head->next;
		}
		if (stack_a->value > head->value)
			stack_a->index++;
		stack_a = stack_a->next;
		i++;
	}
}
