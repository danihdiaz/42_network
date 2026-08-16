/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:01:59 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/16 12:51:22 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	start_threads(t_simulation *sim, pthread_t *threads)
{
	int			i;
	pthread_t	t_monitor;

	pthread_create(&t_monitor, NULL, monitor, sim);
	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_create(&threads[i], NULL, person_life, &sim->people[i]);
		i++;
	}
	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(t_monitor, NULL);
}

int	main(int argc, char **argv)
{
	char			**args;
	t_config		*to_parse;
	t_simulation	*sim;
	pthread_t		*threads;

	if (argc != 9)
		return (printf("U must enter 8 arguments, no less, no more\n"), 1);
	args = malloc(sizeof(char *) * (argc - 1));
	to_parse = malloc(sizeof(t_config));
	if (!to_parse || !args)
		return (free(args), free(to_parse), 1);
	while (argc-- > 1)
		args[argc - 1] = argv[argc];
	if (parser(args, to_parse))
		return (free(args), free(to_parse), 1);
	sim = simulation_init(to_parse);
	if (!sim)
		return (free(args), free(to_parse), 1);
	threads = malloc(sizeof(pthread_t) * to_parse->number_of_coders);
	if (!threads)
		return (clean_simulation(sim), free(args), free(to_parse), 1);
	start_threads(sim, threads);
	clean_simulation(sim);
	return (free(args), free(to_parse), free(threads), 0);
}
