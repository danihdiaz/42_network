/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 20:51:24 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/21 20:53:19 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	register_in_dongle(t_dongle *dongle, t_person *person,
t_wait_node *node)
{
	pthread_mutex_lock(&dongle->lock);
	node->person = person;
	node->arrival_time = get_time_ms();
	node->burnout_deadline = person->last_compile
		+ person->sim->config->time_to_burnout;
	heap_push(&dongle->heap, node, person->sim->config->scheduler);
	pthread_mutex_unlock(&dongle->lock);
}

void	acquire_dongle(t_dongle *dongle, int cooldown, t_person *person)
{
	long	cd_deadline;

	pthread_mutex_lock(&dongle->lock);
	cd_deadline = dongle->last_release + cooldown;
	wait_loop(dongle, cd_deadline, person);
	dongle->is_taken = 1;
	log_message(person, "has taken a dongle");
	pthread_mutex_unlock(&dongle->lock);
}

void	unregister_from_dongle(t_dongle *dongle, t_person *person)
{
	pthread_mutex_lock(&dongle->lock);
	heap_pop(&dongle->heap, person->sim->config->scheduler);
	pthread_mutex_unlock(&dongle->lock);
}

void	release_single_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->is_taken = 0;
	dongle->last_release = get_time_ms();
	pthread_cond_broadcast(&dongle->av_cond);
	pthread_mutex_unlock(&dongle->lock);
}
