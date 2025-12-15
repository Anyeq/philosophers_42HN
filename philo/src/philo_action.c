/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:56:52 by asando            #+#    #+#             */
/*   Updated: 2025/12/13 19:20:09 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO:try ft_log_action after each mutex lock
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
			pthread_mutex_lock(philo->left_fork);
			ft_log_action(philo, "has taken a fork");
			ft_log_action(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			ft_log_action(philo, "has taken a fork");
			ft_log_action(philo, "has taken a fork");
		}
	}
	return ;
}

static void	ft_one_philo_action(t_philo *philo)
{


	pthread_mutex_lock(philo->right_fork);
	if (philo->data->end_simulation == false)
	{
		pthread_mutex_lock(&(philo->data->mutex_print_log));
		printf("%ld %d %s\n", ft_get_time_ms() - philo->data->time_start_ms,
			philo->id, "has taken a fork");
		pthread_mutex_unlock(&(philo->data->mutex_print_log));
	}
	return ;
}

// NOTE: this function act as priority function
static void	ft_action_thinking(t_philo *philo)
{
	long	time_to_think;

	ft_log_action(philo, "is thinking");
	pthread_mutex_lock(&philo->data->mutex_monitor_last_eat_time);
	time_to_think = (philo->data->time_to_die
		- (ft_get_time_ms() - philo->time_last_eat_ms)
		- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->data->mutex_monitor_last_eat_time);
	if (time_to_think < 0)
		time_to_think = 0;
	else if (time_to_think > 0 && philo->n_eat == 0)
		time_to_think = 0;
	else if (time_to_think > 600)
		time_to_think = 200;
	ft_usleep(time_to_think, philo->data);
	return ;
}

static void	ft_finish_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return ;
}

// BUG: when it finished due to enough eating amount, it should stop
// casually instead forcing to stop
static void	ft_action(t_philo *philo)
{
	ft_action_thinking(philo);
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
	while(ft_get_time_ms() < philo->data->time_start_ms)
		continue ;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (1)
	{
		pthread_mutex_lock(&(philo->data->mutex_monitor_simulation_status));
		simulation_status = philo->data->end_simulation;
		pthread_mutex_unlock(&(philo->data->mutex_monitor_simulation_status));
		if (simulation_status)
			return (NULL);
		if (philo->data->n_philo == 1)
			ft_one_philo_action(philo);
		else
			ft_action(philo);
	}
	return (NULL);
}
