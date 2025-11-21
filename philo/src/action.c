/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:56:52 by asando            #+#    #+#             */
/*   Updated: 2025/11/21 20:07:27 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_prepare_to_eat(t_philo *philo)
{
	if (end_condition(philo) == false)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			log_action(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			log_action(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			log_action(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			log_action(philo, "has taken a fork");
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

void	*ft_philo_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (end_condition(philo) == false)
	{
		log_action(philo, "is thinking");
		prepare_to_eat(philo);
		philo->time_last_eat_ms = get_time_ms();
		log_action(philo, "is eating");
		ft_usleep(philo->data->time_to_eat, philo->data);
		finish_eat(philo);
		philo->n_eat++;
		log_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}
