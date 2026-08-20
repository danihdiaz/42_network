/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 17:44:20 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/13 14:14:47 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_atoi_check(char *str)
{
	int	i;
	int	num;

	if (!strcmp(str, ""))
		return (-1);
	if (str[0] == '-')
		return (-1);
	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		else
		{
			if (num > (INT_MAX - (str[i] - 48)) / 10)
				return (-1);
			num = num * 10 + (str[i] - 48);
			i++;
		}
	}
	if (num < 0)
		return (-1);
	return (num);
}

char	**get_names(void)
{
	static char	*names[6];

	names[0] = "number_of_coders";
	names[1] = "time_to_burnout";
	names[2] = "time_to_compile";
	names[3] = "time_to_debug";
	names[4] = "time_to_refactor";
	names[5] = "number_of_compiles_required";
	return (names);
}

void	write_to_config(int index, int value, t_config *conf)
{
	if (index == 0)
		conf->number_of_coders = value;
	if (index == 1)
		conf->time_to_burnout = value;
	if (index == 2)
		conf->time_to_compile = value;
	if (index == 3)
		conf->time_to_debug = value;
	if (index == 4)
		conf->time_to_refactor = value;
	if (index == 5)
		conf->number_of_compiles_required = value;
	if (index == 6)
		conf->dongle_cooldown = value;
	if (index == 7)
		conf->scheduler = value;
}

static int	check_num_arg(char *arg, char *name, int index)
{
	int	num;

	num = ft_atoi_check(arg);
	if (index == 6 && num < 0)
	{
		fprintf(stderr, "Can't use negatives in 'dongle_cooldown'\n");
		return (-1);
	}
	if (index != 6 && num <= 0)
	{
		fprintf(stderr, "Can't use negatives or 0 in '%s'\n", name);
		return (-1);
	}
	return (num);
}

int	parser(char **args, t_config *config)
{
	int		i;
	int		num;
	char	**params;

	i = 0;
	params = get_names();
	while (i < 7)
	{
		num = check_num_arg(args[i], params[i], i);
		if (num == -1)
			return (1);
		write_to_config(i, num, config);
		i++;
	}
	if (!strcmp(args[i], "fifo"))
		write_to_config(i, 0, config);
	else if (!strcmp(args[i], "edf"))
		write_to_config(i, 1, config);
	else
	{
		fprintf(stderr, "scheduler must be either 'fifo' or 'edf'\n");
		return (1);
	}
	return (0);
}
