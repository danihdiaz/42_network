/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:37:02 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/10 20:55:03 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	all_compiled(t_simulation *sim)
{
	int	i;
	int	rquired_comp;
	int	count;

	count = sim->config->number_of_coders;
	i = 0;
	rquired_comp = sim->config->number_of_compiles_required;
	while (1)
	{
		while (count != 0)
		{
			if (i > count)
				i = 0;
			if (sim->people[i].compile_count >= rquired_comp)
				count--;
			i++;
		}
		return (1);
	}
}

long	get_min_burnout(t_simulation *sim, int *index)
{
	int		i;
	long	min;
	long	deadline;

	i = 0;
	min = sim->people[i].last_compile + sim->config->time_to_burnout;
	*index = i;
	while (i < sim->config->number_of_coders)
	{
		deadline = sim->people[i].last_compile + sim->config->time_to_burnout;
		if (deadline < min)
		{
			min = deadline;
			*index = i;
		}
		i++;
	}
	return (min);
}

int	wait_for_burnout(t_simulation *sim, int *indx)
{
	long			min;
	struct timespec	ts;
	int				index;

	index = 0;
	while (1)
	{
		if (all_compiled(sim))
			return (2);
		min = get_min_burnout(sim, &index);
		ts = ms_to_timespec(min);
		if (get_time_ms() >= min)
		{
			*indx = index;
			return (1);
		}
		pthread_mutex_lock(&sim->compile_lock);
		pthread_cond_timedwait(&sim->compile_signal, &sim->compile_lock, &ts);
		pthread_mutex_unlock(&sim->compile_lock);
	}
}

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				stop;
	int				index;

	index = 0;
	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->stop_lock);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->stop_lock);
	while (stop == 0)
		stop = wait_for_burnout(sim, &index);
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_lock);
	if (stop == 2)
		return (NULL);
	printf("%ld %d burned out\n", get_time_ms(), sim->people[index].number);
	return (NULL);
}
