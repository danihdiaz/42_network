/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-25 12:39:52 by dhontani          #+#    #+#             */
/*   Updated: 2026-02-25 12:39:52 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_check_duplicates(char **str)
{
	size_t	i;
	size_t	j;
	long	num1;
	long	num2;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		num1 = ft_atol(str[i]);
		while (str[j])
		{
			num2 = ft_atol(str[j]);
			if (num1 != num2)
				j++;
			if (num1 == num2)
				return (0);
		}
		i++;
	}
	return (1);
}

static char	*ft_strjoin_sep(char *s1, char *s2, char n)
{
	size_t	i;
	size_t	j;
	char	*r;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = n;
	i++;
	j = 0;
	while (s2[j])
	{
		r[i] = s2[j];
		i++;
		j++;
	}
	return (r[i] = '\0', r);
}

long	ft_atol(char *str)
{
	size_t	i;
	long	num;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = str[i] - '0';
		if (res > (LONG_MAX / 10))
			return (0);
		res = res * 10 + num;
		i++;
	}
	return (res * sign);
}

static void	free_all(char *result, char **resjoin)
{
	size_t	i;

	i = 0;
	free(result);
	while (resjoin[i])
	{
		free(resjoin[i]);
		i++;
	}
	free(resjoin);
}

int	ft_check_args(int offset, char **argv)
{
	size_t	j;
	long	tmp;
	char	*result;
	char	**resjoin;

	j = 0;
	result = ft_strdup(argv[offset]);
	if (!result)
		return (0);
	while (argv[offset + 1])
	{
		result = ft_strjoin_sep(result, argv[offset + 1], ' ');
		offset++;
	}
	resjoin = ft_split(result, ' ');
	while (resjoin[j])
	{
		tmp = ft_atol(resjoin[j]);
		if (!ft_is_valid_number(resjoin[j]) || tmp > INT_MAX || tmp < INT_MIN)
			return (free_all(result, resjoin), 0);
		j++;
	}
	if (!ft_check_duplicates(resjoin))
		return (0);
	return (free_all(result, resjoin), 1);
}
