/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 17:52:34 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/10 19:46:58 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char	**get_colors(void)
{
	static char	*colors[7];

	colors[0] = "\033[91m";
	colors[1] = "\033[92m";
	colors[2] = "\033[93m";
	colors[3] = "\033[94m";
	colors[4] = "\033[95m";
	colors[5] = "\033[96m";
	colors[6] = "\033[97m";
	return (colors);
}

void	log_message(t_person *person, char *state)
{
	char	**colors;

	colors = get_colors();
	pthread_mutex_lock(&person->sim->log_lock);
	if (!strcmp(state, "has taken a dongle"))
		printf("%s%ld %d %s\033[0m\n", colors[person->number % 7], get_time_ms(), person->number, state);
	else
		printf("%s%ld %d is %s\033[0m\n", colors[person->number % 7], get_time_ms(), person->number, state);
	pthread_mutex_unlock(&person->sim->log_lock);
}
