/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread_action.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:19:05 by asando            #+#    #+#             */
/*   Updated: 2025/11/23 13:18:07 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NOTE: NOT YET FINISH
// NOTE: ft_log_action need to be check to keep the time consistent
// NOTE: log died case need to be reconsider
static bool	ft_stop_simulation_condition(t_data *data, long time_last_eat_ms,
										 t_philo *philo)
{
	if (ft_get_time_ms() - time_last_eat_ms > data->time_to_die)
	{
		pthread_mutex_lock(&data->mutex_monitor_simulation_status);
		data->end_simulation = true;
		pthread_mutex_unlock(&data->mutex_monitor_simulation_status);
		ft_log_action(philo, "died");
		return (true);
	}
	if (data->philo[i].n_eat == data->n_eat_max)
	{
		pthread_mutex_lock(&data->mutex_monitor_simulation_status);
		data->end_simulation = true;
		pthread_mutex_unlock(&data->mutex_monitor_simulation_status);
		ft_log_action(philo, "died");
		return (true);
	}
	return (false);
}

bool	ft_monitor_action(void *param)
{
	int		i;
	long	time_last_eat_ms;
	t_data	*data;

	i = 0;
	time_last_eat_ms = 0;
	data = (t_data *)param;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->mutex_monitor_last_eat_time);
			time_last_eat_ms = data->philo[i].time_last_eat_ms;
			pthread_mutex_unlock(&data->mutex_monitor_last_eat_time);
			if (ft_stop_simulation_condition(data, time_last_eat_ms, &data->philo[i]))
				break ;
			i++;
		}
		ft_usleep(100, data);
	}
}

static int	ft_init_mutex_monitor(t_data *data)
{
	if (pthread_mutex_init(&(data->mutex_monitor_simulation_status), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_simulation_status");
		return (-1);
	}
	if (pthread_mutex_init(&(data->mutex_monitor_last_eat_time), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_last_eat_time");
		pthread_mutex_destroy(&(data->mutex_monitor_simulation_status));
		return (-1);
	}
	if (pthread_mutex_init(&(data->mutex_monitor_n_eat), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_monitor_n_eat");
		pthread_mutex_destroy(&(data->mutex_monitor_simulation_status));
		pthread_mutex_destroy(&(data->mutex_monitor_last_eat_time));
		return (-1);
	}
	return (0);
}

int	ft_start_monitoring_thread(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_philo > 1)
	{
		if (pthread_create(&(data->monitor_thread), NULL, ft_monitor_action,
					 (void *)data)
		{
			ft_system_failed(THREAD_FAIL, "data->monitor_thread");
			ft_destroy_mutex(data);
			return (-1);
		}
		if (ft_init_mutex_monitor(data))
		{
			pthread_join(data->monitor_thread, NULL);
			ft_destroy_mutex(data);
			return (-1);
		}
	}
	return (0);
}
