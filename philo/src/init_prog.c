/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:50:19 by asando            #+#    #+#             */
/*   Updated: 2025/10/27 13:55:30 by asando           ###   ########.fr       */
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
	if (pthread_mutex_init(&(data->mutex_print), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_print");
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

static int	ft_start_suthread(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_philo > 1)
	{
		if (pthread_create(&(data->super_thread), NULL, super_action,
					 (void *)data)
		{
			ft_system_failed(THREAD_FAIL, "data->super_thread");
			return (-1);
		}
	}
	if (pthread_mutex_init(&(data->mutex_sim), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_sim");
		while (i < data->n_philo)
			pthread_mutex_destroy(&(data->fork[i++]));
		pthread_mutex_destroy(&(data->mutex_print));
		pthread_join(data->super_thread, NULL);
		return (-1);
	}
	return (0);
}

// TODO: on the ft_get_time_ms() should make it more presice
static int	ft_start_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->time_start_ms = ft_get_time_ms();
	while (i < data->n_philo)
	{
		philo[i].time_last_eat_ms = ft_get_time_ms();
		if (pthread_create(&(philo[i].thread), NULL, philo_action,
					 (void *)(philo[i]))
		{
			ft_system_failed(THREAD_FAIL, "philo->thread");
			while (--i >= 0)
				pthread_join(philo[i].thread, NULL);
			return (-1);
		}
		i++;
	}
	if (ft_start_suthread(data))
	{
		while (--i >= 0)
			pthread_join(philo[i].thread, NULL);
		return (-1);
	}
	return (0);
}

int	ft_init_thread(t_data *data, t_philo **philo)
{
	*philo = malloc(sizeof(t_philo) * data->n_philo);
	if (*philo == NULL)
	{
		ft_system_failed("philo");
		return (-1);
	}
	data->philo = *philo;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (data->fork == NULL)
	{
		ft_system_failed("data->fork");
		return (-1);
	}
	if (init_mutex(data) == -1)
		return (-1);
	init_philo(data, *philo);
	if (ft_start_thread(data, *philo) == -1)
		return (-1);
	return (0);
}
