/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 19:22:48 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/20 20:31:18 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_stop(t_simulation *sim)
{
	int	stop;

	pthread_mutex_lock(&sim->stop_lock);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->stop_lock);
	return (stop);
}

struct timespec	ms_to_timespec(long time)
{
	struct timespec	timespc;

	timespc.tv_sec = time / 1000;
	timespc.tv_nsec = (time % 1000) * 1000000;
	return (timespc);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_real_time_ms(t_simulation *sim)
{
	return (get_time_ms() - sim->start);
}

void	clean_simulation(t_simulation *sim)
{
	if (!sim)
		return ;
	clean_dongles(sim);
	clean_people(sim);
	pthread_mutex_destroy(&sim->compile_lock);
	pthread_mutex_destroy(&sim->log_lock);
	pthread_mutex_destroy(&sim->stop_lock);
	pthread_cond_destroy(&sim->compile_signal);
	free(sim);
}
