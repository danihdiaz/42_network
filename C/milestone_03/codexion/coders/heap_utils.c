/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 19:49:44 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/11 20:15:41 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_parent(int index)
{
	return ((index - 1) / 2);
}

int	get_left(int index)
{
	return ((index * 2 + 1));
}

int	get_right(int index)
{
	return ((index * 2 + 2));
}

void	swap_nodes(t_wait_node *new, t_wait_node *old)
{
	t_wait_node	temp;

	temp = *new;
	*new = *old;
	*old = temp;
}

int	has_priority(t_wait_node *new, t_wait_node *old, int mode)
{
	if (mode == 0)
		return (new->arrival_time < old->arrival_time);
	else if (mode == 1)
	{
		if (new->burnout_deadline < old->burnout_deadline)
			return (1);
		if (new->burnout_deadline == old->burnout_deadline)
			return (new->arrival_time < old->arrival_time);
	}
	return (0);
}
