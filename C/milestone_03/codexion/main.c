/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:01:59 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/10 19:11:09 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	int				i;
	int				j;
	char			**args;
	t_config		*to_parse;
	t_simulation	*simulation;
	pthread_t		*threads;
	pthread_t		t_monitor;

	if (argc != 9)
		return (1);
	i = 1;
	j = 0;
	args = malloc(sizeof(char *) * (argc - 1));
	to_parse = malloc(sizeof(t_config));
	while (argv[i])
	{
		args[j] = argv[i];
		i++;
		j++;
	}
	if (parser(args, to_parse))
		return (1);
	simulation = simulation_init(to_parse);
	threads = malloc(sizeof(pthread_t) * to_parse->number_of_coders);
	i = 0;
	pthread_create(&t_monitor, NULL, monitor, simulation);
	while (i < to_parse->number_of_coders)
	{
		pthread_create(&threads[i], NULL, person_life, &simulation->people[i]);
		i++;
	}
	i = 0;
	while (i < to_parse->number_of_coders)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(t_monitor, NULL);
	return (0);
}
