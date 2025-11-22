/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:50:19 by asando            #+#    #+#             */
/*   Updated: 2025/11/22 22:01:22 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
		{
			ft_system_failed(MUTEX_FAIL, "data->fork");
			while (--i >= 0)
				pthread_mutex_destroy(&(data->fork[i]));
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&(data->mutex_print_log), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_print_log");
		while (--i >= 0)
			pthread_mutex_destroy(&(data->fork[i]));
		return (-1);
	}
	return (0);
}

static int	ft_init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while(i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].n_eat = 0;
		philo[i].right_fork = &data->fork[i];
		philo[i].left_fork = &data->fork[(i + 1) % data->n_philo];
		philo[i].data = data;
		i++;
	}
	return (0);
}

// TODO: on the ft_get_time_ms() should make it more presice
int	ft_init_simulation(t_data *data, t_philo **philo)
{
	*philo = malloc(sizeof(t_philo) * data->n_philo);
	if (*philo == NULL)
	{
		ft_system_failed(MALLOC_FAIL, "philo");
		return (-1);
	}
	data->philo = *philo;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (data->fork == NULL)
	{
		ft_system_failed(MALLOC_FAIL, "data->fork");
		return (-1);
	}
	if (ft_init_mutex(data) == -1)
		return (-1);
	ft_init_philo(data, *philo);
	return (0);
}
