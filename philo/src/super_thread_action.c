/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_thread_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:19:05 by asando            #+#    #+#             */
/*   Updated: 2025/11/21 20:08:08 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NOTE: NOT YET FINISH
// NOTE: mutex_time_check not yet initialize
static bool	ft_hunger_condition(t_data *data)
{
	int		i;
	long	time_now;

	i = 0;
	time_now = 0;
	while (data->end_simulation == false)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->mutex_time_check);
			time_now = ft_get_time_ms();
			if (time_now - data->philo[i].time_last_eat_ms > data->time_to_die)
			{
				pthread_mutex_lock(&data->mutex_sim);
				data->end_simulation = true;
				log_action(&philo[i], "died");
				pthread_mutex_unlock(&data->mutex_sim);
				pthread_mutex_unlock(&data->mutex_time_check);
				return ;
			}
			pthread_mutex_unlock(&data->mutex_time_check);
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
