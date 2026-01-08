/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread_action.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:19:05 by asando            #+#    #+#             */
/*   Updated: 2026/01/08 16:48:53 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_stop_simulation_condition(t_data *data, t_philo *philo)
{
	long	current_time;
	long	time_last_eat_ms;

	time_last_eat_ms = 0;
	pthread_mutex_lock(&philo->mutex_last_eat_time);
	time_last_eat_ms = philo->time_last_eat_ms;
	pthread_mutex_unlock(&philo->mutex_last_eat_time);
	current_time = ft_get_time_ms();
	if (current_time - time_last_eat_ms > data->time_to_die)
	{
		pthread_mutex_lock(&data->mutex_monitor_simulation_status);
		data->end_simulation = true;
		pthread_mutex_unlock(&data->mutex_monitor_simulation_status);
		pthread_mutex_lock(&(data->mutex_print_log));
		printf("%ld %d %s\n", current_time - philo->data->time_start_ms,
			philo->id, "died");
		pthread_mutex_unlock(&(data->mutex_print_log));
		return (true);
	}
	return (false);
}

static bool	ft_all_eat_enough(t_data *data)
{
	int	i;

	i = 0;
	while (data->n_eat_max >= 0 && i < data->n_philo)
	{
		pthread_mutex_lock(&data->philo[i].mutex_n_eat);
		if (data->philo[i].n_eat < data->n_eat_max)
		{
			pthread_mutex_unlock(&data->philo[i].mutex_n_eat);
			return (false);
		}
		pthread_mutex_unlock(&data->philo[i].mutex_n_eat);
		i++;
	}
	pthread_mutex_lock(&data->mutex_monitor_simulation_status);
	data->end_simulation = true;
	pthread_mutex_unlock(&data->mutex_monitor_simulation_status);
	return (true);
}

static bool	ft_simulation_status(t_data *data)
{
	bool	status;

	pthread_mutex_lock(&data->mutex_monitor_simulation_status);
	status = data->end_simulation;
	pthread_mutex_unlock(&data->mutex_monitor_simulation_status);
	return (status);
}

static void	*ft_monitor_action(void *param)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)param;
	while (ft_get_time_ms() < data->time_start_ms)
		ft_usleep(1, data);
	while (!ft_simulation_status(data))
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (ft_stop_simulation_condition(data, &data->philo[i]))
				break ;
			i++;
		}
		if (ft_all_eat_enough(data) == true)
			return (NULL);
		ft_usleep(1, data);
	}
	return (NULL);
}

int	ft_start_monitoring_thread(t_data *data)
{
	if (pthread_create(&(data->monitor_thread), NULL, ft_monitor_action,
			(void *)data))
	{
		ft_system_failed(THREAD_FAIL, "data->monitor_thread");
		pthread_mutex_destroy(&data->mutex_monitor_simulation_status);
		ft_destroy_mutex(data);
		ft_destroy_mutex_eat(data, 2, data->n_philo);
		return (-1);
	}
	return (0);
}
