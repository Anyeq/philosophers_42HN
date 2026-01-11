/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:56:52 by asando            #+#    #+#             */
/*   Updated: 2026/01/11 18:57:48 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_log_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	ft_log_action(philo, "has taken a fork");
	return ;
}

static void	ft_think(t_philo *philo)
{
	long	time_to_think;
	long	time_last_eat;

	ft_log_action(philo, "is thinking");
	pthread_mutex_lock(&philo->mutex_last_eat_time);
	time_last_eat = philo->time_last_eat_ms;
	pthread_mutex_unlock(&philo->mutex_last_eat_time);
	time_to_think = (philo->data->time_to_die
			- (ft_get_time_ms() - time_last_eat)
			- philo->data->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	else if (time_to_think > 600)
		time_to_think = 200;
	ft_usleep(time_to_think, philo->data);
	return ;
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex_last_eat_time));
	philo->time_last_eat_ms = ft_get_time_ms();
	pthread_mutex_unlock(&(philo->mutex_last_eat_time));
	pthread_mutex_lock(&(philo->mutex_n_eat));
	philo->n_eat++;
	pthread_mutex_unlock(&(philo->mutex_n_eat));
	ft_log_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}

static void	ft_action(t_philo *philo)
{
	ft_take_fork(philo);
	ft_eat(philo);
	ft_log_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
	ft_think(philo);
	return ;
}

void	*ft_philo_action(void *arg)
{
	t_philo	*philo;
	bool	simulation_status;

	philo = (t_philo *)arg;
	while (ft_get_time_ms() < philo->data->time_start_ms)
		ft_usleep(1, philo->data);
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (1)
	{
		if (philo->data->n_philo == 1)
			ft_one_philo_action(philo);
		else
			ft_action(philo);
		pthread_mutex_lock(&(philo->data->mutex_monitor_simulation_status));
		simulation_status = philo->data->end_simulation;
		pthread_mutex_unlock(&(philo->data->mutex_monitor_simulation_status));
		if (simulation_status)
			return (NULL);
	}
	return (NULL);
}
