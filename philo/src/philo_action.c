/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:56:52 by asando            #+#    #+#             */
/*   Updated: 2025/11/23 15:00:04 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_prepare_to_eat(t_philo *philo)
{
	bool	simulation_status;

	pthread_mutex_lock(&(philo->data->mutex_monitor_simulation_status));
	simulation_status = philo->data->end_simulation;
	pthread_mutex_unlock(&(philo->data->mutex_monitor_simulation_status));
	if (simulation_status == false)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			ft_log_action(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			ft_log_action(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			ft_log_action(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			ft_log_action(philo, "has taken a fork");
		}
	}
	return ;
}

static void	ft_finish_eat(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}

static void	ft_action(t_philo *philo)
{
	ft_log_action(philo, "is thinking");
	ft_prepare_to_eat(philo);
	pthread_mutex_lock(&(philo->data->mutex_monitor_last_eat_time));
	philo->time_last_eat_ms = ft_get_time_ms();
	pthread_mutex_unlock(&(philo->data->mutex_monitor_last_eat_time));
	ft_log_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	ft_finish_eat(philo);
	pthread_mutex_lock(&(philo->data->mutex_monitor_n_eat));
	philo->n_eat++;
	pthread_mutex_unlock(&(philo->data->mutex_monitor_n_eat));
	ft_log_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
	return ;
}

void	*ft_philo_action(void *arg)
{
	t_philo	*philo;
	bool	simulation_status;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (1)
	{
		pthread_mutex_lock(&(philo->data->mutex_monitor_simulation_status));
		simulation_status = philo->data->end_simulation;
		pthread_mutex_unlock(&(philo->data->mutex_monitor_simulation_status));
		if (simulation_status)
			return (NULL);
		ft_action(philo);
	}
	return (NULL);
}
