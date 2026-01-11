/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:15:29 by asando            #+#    #+#             */
/*   Updated: 2026/01/11 19:33:52 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo_action(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&(philo->data->mutex_print_log));
	printf("%ld %d %s\n", ft_get_time_ms() - philo->data->time_start_ms,
		philo->id, "has taken a fork");
	pthread_mutex_unlock(&(philo->data->mutex_print_log));
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}
