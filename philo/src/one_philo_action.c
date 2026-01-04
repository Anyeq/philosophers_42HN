/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:15:29 by asando            #+#    #+#             */
/*   Updated: 2026/01/04 15:31:11 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo_action(t_philo *philo)
{
	if (philo->has_fork == false)
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->data->end_simulation == false)
		{
			pthread_mutex_lock(&(philo->data->mutex_print_log));
			printf("%ld %d %s\n", ft_get_time_ms() - philo->data->time_start_ms,
				philo->id, "has taken a fork");
			pthread_mutex_unlock(&(philo->data->mutex_print_log));
		}
		philo->has_fork = true;
	}
	ft_usleep(10, philo->data);
	if (philo->data->end_simulation == true)
		pthread_mutex_unlock(philo->right_fork);
	return ;
}
