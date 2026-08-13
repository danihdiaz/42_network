/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 18:34:00 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/12 18:10:34 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_push(t_heap *heap, t_wait_node *new, int mode)
{
	int	i;

	i = heap->current_size;
	heap->nodes[i] = *new;
	heap->current_size++;
	while (i > 0)
	{
		if (!has_priority(&heap->nodes[i], &heap->nodes[get_parent(i)], mode))
			break ;
		swap_nodes(&heap->nodes[i], &heap->nodes[get_parent(i)]);
		i = get_parent(i);
	}
}

static int	get_best_node(t_heap *heap, int i, int mode)
{
	int	best;
	int	right;
	int	left;

	best = i;
	right = get_right(i);
	left = get_left(i);
	if (left < heap->current_size
		&& has_priority(&heap->nodes[left], &heap->nodes[best], mode))
		best = left;
	if (right < heap->current_size
		&& has_priority(&heap->nodes[right], &heap->nodes[best], mode))
		best = right;
	return (best);
}

t_wait_node	heap_pop(t_heap *heap, int mode)
{
	int			i;
	int			right;
	int			left;
	int			best;
	t_wait_node	topop;

	i = 0;
	topop = heap->nodes[0];
	heap->current_size--;
	heap->nodes[0] = heap->nodes[heap->current_size];
	while (1)
	{
		best = get_best_node(heap, i, mode);
		if (best == i)
			break ;
		swap_nodes(&heap->nodes[i], &heap->nodes[best]);
		i = best;
	}
	return (topop);
}
