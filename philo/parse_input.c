/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:10:56 by asando            #+#    #+#             */
/*   Updated: 2025/10/10 14:53:52 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usage(void)
{
	printf("Usage philo <number_of_philosophers> " 
			" <time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_time_each_philosophers_need_to_eat]");
}

static int	ft_isdigit(unsigned char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_valid(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

static int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + ((*str - '0') * sign);
		str++;
	}
	return (res);
}

int	parse_input(int argc, char **argv, t_data *data)
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
		if (!ft_is_valid(argv[i++]))
		{
			ft_usage();
			return (-1);
		}
	}
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_to_eat = ft_atoi(argv[5]);
	return (0);
}
