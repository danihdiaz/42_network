/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 12:13:57 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/13 18:01:02 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	clean_heap(t_dongle *dongle)
{
	if (!dongle)
		return ;
	if (dongle->heap.nodes)
	{
		free(dongle->heap.nodes);
		dongle->heap.nodes = NULL;
		dongle->heap.capacity = 0;
		dongle->heap.capacity = 0;
	}
}

void	clean_dongles(t_simulation *sim)
{
	int	i;

	if (!sim || !sim->dongles)
		return ;
	i = 0;
	while (i < sim->config->number_of_coders)
	{
		clean_heap(&sim->dongles[i]);
		pthread_mutex_destroy(&sim->dongles[i].lock);
		pthread_cond_destroy(&sim->dongles[i].av_cond);
		i++;
	}
	free(sim->dongles);
	sim->dongles = NULL;
}

void	clean_people(t_simulation *sim)
{
	if (!sim || !sim->people)
		return ;
	free(sim->people);
	sim->people = NULL;
}
