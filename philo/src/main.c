/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:42:31 by asando            #+#    #+#             */
/*   Updated: 2025/11/21 20:25:04 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&(data->fork[i++]));
	pthread_mutex_destroy(&(data->mutex_print));
	return ;
}

static void	ft_join_thread(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_philo)
		pthread_join(data->philo[i++].thread, NULL);
	if (data->n_philo > 1)
		pthread_join(data->monitor_thread, NULL);
	return ;
}

// NOTE: Forgett what mutex_sim for
static int	ft_start_monitoring_thread(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_philo > 1)
	{
		if (pthread_create(&(data->monitor_thread), NULL, monitor_action,
					 (void *)data)
		{
			ft_system_failed(THREAD_FAIL, "data->super_thread");
			ft_destroy_mutex(data);
			return (-1);
		}
	}
	if (pthread_mutex_init(&(data->mutex_sim), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_sim");
		ft_destroy_mutex(data);
		pthread_join(data->monitor_thread, NULL);
		return (-1);
	}
	return (0);
}

// NOTE: check ft_start_monitoring_thread
static int	ft_start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->time_start_ms = ft_get_time_ms();
	while (i < data->n_philo)
	{
		philo[i].time_last_eat_ms = ft_get_time_ms();
		if (pthread_create(&(philo[i].thread), NULL, ft_philo_action,
					 (void *)(philo[i]))
		{
			ft_system_failed(THREAD_FAIL, "philo->thread");
			while (--i >= 0)
				pthread_join(philo[i].thread, NULL);
			ft_destroy_mutex(data);
			return (-1);
		}
		i++;
	}
	if (ft_start_monitoring_thread(data))
	{
		ft_join_thread(data);
		return (-1);
	}
	return (0);
}

// NOTE: Usage philo 4 100 100 100 || philo 4 100 100 100 5
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (ft_parse_input(argc, argv, &data) == -1)
		return (-1);
	if (ft_init_simulation(&data, &philo) == -1)
	{
		ft_free_alloc(&philo, &data);
		return (-1);
	}
	if (ft_start_simulation(&data, philo) == -1)
	{
		ft_free_alloc(&philo, &data);
		return (-1);
	}
	ft_join_thread(&data);
	ft_destroy_mutex(&data);
	ft_free_alloc(&philo, &data);
	return (0);
}
