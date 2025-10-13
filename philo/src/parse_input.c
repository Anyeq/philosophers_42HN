/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:10:56 by asando            #+#    #+#             */
/*   Updated: 2025/10/13 14:06:17 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usage(void)
{
	printf("Usage philo <number_of_philosophers> " 
			" <time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_time_each_philosophers_need_to_eat]");
}

static int	is_valid(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

static int	check_input_error(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_usage();
		return (-1);
	}
	while (i < argc)
	{
		if (i == 1 && ft_atoi(argv[1]) < 1)
		{
			ft_usage();
			return (-1);
		}
		if (!is_valid(argv[i++]))
		{
			ft_usage();
			return (-1);
		}
	}
	return (0);
}

int	parse_input(int argc, char **argv, t_data *data)
{
	if (check_input_error(argc, argv) == -1)
		return (-1);
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat_max = ft_atoi(argv[5]);
	data->end_simulation = false;
	data->fork = NULL;
	return (0);
}
