/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_thread_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:19:05 by asando            #+#    #+#             */
/*   Updated: 2025/11/22 21:59:15 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NOTE: NOT YET FINISH
// NOTE: mutex_time_check not yet initialize
static bool	ft_stop_simulation_condition(t_data *data)
{
	int		i;
	long	time_now;
	long	time_last_eat_ms;

	i = 0;
	time_now = 0;
	time_last_eat_ms = 0;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->mutex_time_check);
			time_last_eat_ms = data->philo[i].time_last_eat_ms;
			pthread_mutex_unlock(&data->mutex_time_check);
			time_now = ft_get_time_ms();
			if (time_now - time_last_eat_ms > data->time_to_die || data->philo[i].n_eat)
			{
				pthread_mutex_lock(&data->mutex_sim);
				data->end_simulation = true;
				pthread_mutex_unlock(&data->mutex_sim);
				ft_log_action(&philo[i], "died");
				return ;
			}
			if (data->philo[i].n_eat == data->n_eat_max)
			{
				pthread_mutex_lock(&data->mutex_sim);
				data->end_simulation = true;
				pthread_mutex_unlock(&data->mutex_sim);
				ft_log_action(&philo[i], "died");
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}

void	*ft_monitor_action(void *arg)
{
	t_data	*data;
	int		i;
	long	time_now;

	i = 0;
	time_now = 0;
	data = (t_data *)param;
	while (data->end_simulation == false)
	{
		i = 0;
		while (i < data->n_philo)
		{

		}
	}
	return (NULL);
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
			while (i < data->n_philo)
				pthread_mutex_destroy(&(data->fork[i++]));
			pthread_mutex_destroy(&(data->mutex_print_log));
			return (-1);
		}
	}
	return (0);
}
