/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:02:13 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/11 19:03:03 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_get_strategy(char *arg)
{
	if (!ft_strncmp(arg, "--simple", 9))
		return (SIMPLE);
	if (!ft_strncmp(arg, "--medium", 9))
		return (MEDIUM);
	if (!ft_strncmp(arg, "--complex", 10))
		return (COMPLEX);
	if (!ft_strncmp(arg, "--adaptive", 11))
		return (ADAPTIVE);
	return (-1);
}

int	ft_parse_flags(int argc, char **argv, int *strategy, int *bench)
{
	size_t	i;

	i = 1;
	while (i < (size_t)argc)
	{
		if (ft_get_strategy(argv[i]) != -1)
		{
			if (*strategy != -1)
				return (0);
			*strategy = ft_get_strategy(argv[i]);
		}
		else if (!ft_strncmp(argv[i], "--bench", 8))
			*bench = 1;
		i++;
	}
	if (*strategy == -1)
		*strategy = ADAPTIVE;
	return (1);
}
