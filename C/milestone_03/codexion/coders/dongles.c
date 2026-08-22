/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 18:18:44 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/21 20:52:27 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	wait_loop(t_dongle *dongle, long cd_deadline, t_person *person)
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

int	get_dongles(t_person *person)
{
	int			cd;
	t_wait_node	node_first;
	t_wait_node	node_second;
	t_dongle	*first;
	t_dongle	*second;

	cd = person->sim->config->dongle_cooldown;
	if (person->left < person->right)
	{
		first = person->left;
		second = person->right;
	}
	else
	{
		first = person->right;
		second = person->left;
	}
	register_in_dongle(first, person, &node_first);
	register_in_dongle(second, person, &node_second);
	acquire_dongle(first, cd, person);
	unregister_from_dongle(first, person);
	acquire_dongle(second, cd, person);
	unregister_from_dongle(second, person);
	return (0);
}

void	release_dongles(t_person *person)
{
	release_single_dongle(person->right);
	release_single_dongle(person->left);
}
