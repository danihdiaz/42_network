/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 13:11:55 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/10 20:21:40 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	refactor(t_person *person)
{
	log_message(person, "refactoring");
	usleep(person->sim->config->time_to_refactor * 1000);
}

void	debug(t_person *person)
{
	log_message(person, "debugging");
	usleep(person->sim->config->time_to_debug * 1000);
}

void	compile(t_person *person)
{
	person->last_compile = get_time_ms();
	log_message(person, "compiling");
	usleep(person->sim->config->time_to_compile * 1000);
	pthread_mutex_lock(&person->sim->compile_lock);
	person->compile_count++;
	pthread_cond_broadcast(&person->sim->compile_signal);
	pthread_mutex_unlock(&person->sim->compile_lock);
}

void	*person_life(void *arg)
{
	t_person		*person;
	int				stop;

	person = (t_person *)arg;
	pthread_mutex_lock(&person->sim->stop_lock);
	stop = person->sim->stop;
	pthread_mutex_unlock(&person->sim->stop_lock);
	while (stop == 0)
	{
		if (get_dongles(person))
		{
			release_dongles(person);
			return (NULL);
		}
		compile(person);
		release_dongles(person);
		if (check_stop(person->sim))
			return (NULL);
		debug(person);
		if (check_stop(person->sim))
			return (NULL);
		refactor(person);
		if (check_stop(person->sim))
			return (NULL);
	}
	return (NULL);
}
