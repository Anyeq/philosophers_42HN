/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:43:03 by asando            #+#    #+#             */
/*   Updated: 2026/01/06 15:35:06 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_valid(char *str)
{
	if (*str == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

static int	ft_check_input_error(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_usage(INVALID_NPARAMS);
		return (-1);
	}
	while (i < argc)
	{
		if (i == 1 && ft_atoi(argv[1]) < 1)
		{
			ft_usage(INVALID_NPHILO);
			return (-1);
		}
		if (!ft_is_valid(argv[i++]))
		{
			ft_usage(INVALID_INPUT);
			return (-1);
		}
	}
	return (0);
}

int	ft_parse_input(int argc, char **argv, t_data *data)
{
	if (ft_check_input_error(argc, argv) == -1)
		return (-1);
	data->n_philo = ft_atoi(argv[1]);
	if (data->n_philo > 200)
		ft_usage(INVALID_NPHILO_MAX);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat_max = ft_atoi(argv[5]);
	else if (argc < 6)
		data->n_eat_max = -1;
	data->end_simulation = false;
	data->fork = NULL;
	data->philo = NULL;
	return (0);
}
