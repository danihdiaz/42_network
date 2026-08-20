/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 18:34:45 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/20 13:23:59 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle	*dongle_init(int number)
{
	t_dongle	*dongles;
	int			index;

	dongles = malloc(sizeof(t_dongle) * number);
	if (!dongles)
		return (NULL);
	index = 0;
	while (index < number)
	{
		pthread_mutex_init(&dongles[index].lock, NULL);
		dongles[index].last_release = 0;
		dongles[index].is_taken = 0;
		pthread_cond_init(&dongles[index].av_cond, NULL);
		heap_init(&dongles[index].heap, number);
		index++;
	}
	return (dongles);
}

t_person	*people_init(int number, t_dongle *dongles, t_simulation *simu)
{
	t_person	*people;
	int			index;
	int			fix;

	index = 0;
	fix = number;
	people = malloc(sizeof(t_person) * number);
	if (!people)
		return (NULL);
	while (number > 0)
	{
		people[index].number = index + 1;
		people[index].compile_count = 0;
		people[index].last_compile = get_time_ms();
		people[index].right = &dongles[index];
		people[index].left = &dongles[((index - 1) + fix) % fix];
		people[index].sim = simu;
		number--;
		index++;
	}
	return (people);
}

t_simulation	*simulation_init(t_config *config)
{
	t_dongle		*dongles;
	t_person		*people;
	t_simulation	*simulation;

	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->config = config;
	dongles = dongle_init(config->number_of_coders);
	simulation->dongles = dongles;
	people = people_init(config->number_of_coders, dongles, simulation);
	simulation->people = people;
	pthread_mutex_init(&simulation->log_lock, NULL);
	simulation->stop = 0;
	simulation->start = get_time_ms();
	pthread_mutex_init(&simulation->stop_lock, NULL);
	pthread_mutex_init(&simulation->compile_lock, NULL);
	pthread_cond_init(&simulation->compile_signal, NULL);
	return (simulation);
}

void	*heap_init(t_heap *heap, int capacity)
{
	heap->nodes = malloc(sizeof(t_wait_node) * capacity);
	if (!heap->nodes)
		return (NULL);
	heap->current_size = 0;
	heap->capacity = capacity;
	return (heap);
}
