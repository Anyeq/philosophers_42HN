/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:42:31 by asando            #+#    #+#             */
/*   Updated: 2026/01/05 14:35:14 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&(data->fork[i++]));
	pthread_mutex_destroy(&(data->mutex_print_log));
	return ;
}

void	ft_join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_join(data->philo[i++].thread, NULL);
	return ;
}

static void	ft_stop_simulation(t_data *data)
{
	pthread_join(data->monitor_thread, NULL);
	ft_destroy_mutex(data);
	pthread_mutex_destroy(&(data->mutex_monitor_simulation_status));
	pthread_mutex_destroy(&(data->mutex_monitor_last_eat_time));
	pthread_mutex_destroy(&(data->mutex_monitor_n_eat));
	return ;
}

static int	ft_start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->time_start_ms = ft_get_time_ms() + (20 * data->n_philo);
	while (i < data->n_philo)
		philo[i++].time_last_eat_ms = data->time_start_ms;
	i = 0;
	if (ft_start_monitoring_thread(data))
		return (-1);
	while (i < data->n_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, ft_philo_action,
				(void *)(&philo[i])))
		{
			ft_system_failed(THREAD_FAIL, "philo->thread");
			while (--i >= 0)
				pthread_join(philo[i].thread, NULL);
			ft_stop_simulation(data);
			return (-1);
		}
		i++;
	}
	return (0);
}

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
	ft_stop_simulation(&data);
	ft_free_alloc(&philo, &data);
	return (0);
}
