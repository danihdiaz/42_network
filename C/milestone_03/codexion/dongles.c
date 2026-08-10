/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 18:18:44 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/10 20:14:20 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	wait_for_dongle(t_dongle *dongle, int cooldown, t_person *person)
{
	long			cd_deadline;
	struct timespec	cd;

	pthread_mutex_lock(&dongle->lock);
	cd_deadline = dongle->last_release + cooldown;
	cd = ms_to_timespec(cd_deadline);
	while (get_time_ms() < cd_deadline && !check_stop(person->sim))
		pthread_cond_timedwait(&dongle->cooldown, &dongle->lock, &cd);
	if (check_stop(person->sim))
		return (1);
	log_message(person, "has taken a dongle");
	return (0);
}

int	get_dongles(t_person *person)
{
	int	cd;
	int	aborted;

	aborted = 0;
	cd = person->sim->config->dongle_cooldown;
	if (person->number % 2 == 0)
	{
		if (wait_for_dongle(person->right, cd, person))
			aborted = 1;
		if (wait_for_dongle(person->left, cd, person))
			aborted = 1;
	}
	else
	{
		if (wait_for_dongle(person->left, cd, person))
			aborted = 1;
		if (wait_for_dongle(person->right, cd, person))
			aborted = 1;
	}
	return (aborted);
}

void	release_dongles(t_person *person)
{
	long	time;

	pthread_mutex_unlock(&person->right->lock);
	pthread_mutex_unlock(&person->left->lock);
	time = get_time_ms();
	person->right->last_release = time;
	person->left->last_release = time;
}
