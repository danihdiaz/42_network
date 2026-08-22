/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:37:02 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/22 19:53:27 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	all_compiled(t_simulation *sim)
{
	int	i;
	int	rquired_comp;

	i = 0;
	rquired_comp = sim->config->number_of_compiles_required;
	while (i < sim->config->number_of_coders)
	{
		if (sim->people[i].compile_count < rquired_comp)
			return (0);
		i++;
	}
	return (1);
}

long	get_min_burnout(t_simulation *sim, int *index)
{
	int		i;
	long	min;
	long	deadline;

	i = 0;
	min = sim->people[i].last_compile + sim->config->time_to_burnout;
	*index = 0;
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
	pthread_mutex_lock(&sim->compile_lock);
	while (!check_stop(sim))
	{
		if (all_compiled(sim))
		{
			pthread_mutex_unlock(&sim->compile_lock);
			return (2);
		}
		min = get_min_burnout(sim, &index);
		if (get_time_ms() >= min)
		{
			*indx = index;
			pthread_mutex_unlock(&sim->compile_lock);
			return (1);
		}
		ts = ms_to_timespec(min);
		pthread_cond_timedwait(&sim->compile_signal, &sim->compile_lock, &ts);
	}
	pthread_mutex_unlock(&sim->compile_lock);
	return (0);
}

void	print_end(t_simulation *sim, int mode, int index)
{
	pthread_mutex_lock(&sim->log_lock);
	if (mode == 1)
		printf("%ld %d burned out\n", get_time_ms() - sim->start,
			sim->people[index].number);
	else
		printf("All coders completed %d compilations!\n",
			sim->config->number_of_compiles_required);
	pthread_mutex_unlock(&sim->log_lock);
}

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				status;
	int				index;

	sim = (t_simulation *)arg;
	index = 0;
	status = wait_for_burnout(sim, &index);
	if (status == 0)
		return (NULL);
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_lock);
	print_end(sim, status, index);
	return (NULL);
}
