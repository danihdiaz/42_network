/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 18:18:44 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/13 19:10:39 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wait_loop(t_dongle *dongle, long cd_deadline, t_person *person)
{
	struct timespec	cd;

	cd = ms_to_timespec(cd_deadline);
	while (!check_stop(person->sim) && (dongle->is_taken
			|| get_time_ms() < cd_deadline
			|| dongle->heap.nodes[0].person != person))
	{
		if (dongle->is_taken)
			pthread_cond_wait(&dongle->av_cond, &dongle->lock);
		else if (get_time_ms() < cd_deadline)
			pthread_cond_timedwait(&dongle->av_cond, &dongle->lock, &cd);
		else
			pthread_cond_wait(&dongle->av_cond, &dongle->lock);
		cd_deadline = dongle->last_release
			+ person->sim->config->dongle_cooldown;
		cd = ms_to_timespec(cd_deadline);
	}
}

int	wait_for_dongle(t_dongle *dongle, int cooldown, t_person *person)
{
	long			cd_deadline;
	t_wait_node		node;

	pthread_mutex_lock(&dongle->lock);
	node.person = person;
	node.arrival_time = get_time_ms();
	node.burnout_deadline = person->last_compile
		+ person->sim->config->time_to_burnout;
	heap_push(&dongle->heap, &node, person->sim->config->scheduler);
	cd_deadline = dongle->last_release + cooldown;
	wait_loop(dongle, cd_deadline, person);
	heap_pop(&dongle->heap, person->sim->config->scheduler);
	dongle->is_taken = 1;
	log_message(person, "has taken a dongle");
	pthread_mutex_unlock(&dongle->lock);
	return (0);
}

static void	release_single_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->is_taken = 0;
	dongle->last_release = get_time_ms();
	pthread_cond_broadcast(&dongle->av_cond);
	pthread_mutex_unlock(&dongle->lock);
}

int	get_dongles(t_person *person)
{
	int	cd;

	cd = person->sim->config->dongle_cooldown;
	if (person->number % 2 == 0)
	{
		if (wait_for_dongle(person->right, cd, person))
			return (1);
		if (wait_for_dongle(person->left, cd, person))
		{
			release_single_dongle(person->right);
			return (1);
		}
	}
	else
	{
		if (wait_for_dongle(person->left, cd, person))
			return (1);
		if (wait_for_dongle(person->right, cd, person))
		{
			release_single_dongle(person->left);
			return (1);
		}
	}
	return (0);
}

void	release_dongles(t_person *person)
{
	release_single_dongle(person->right);
	release_single_dongle(person->left);
}
