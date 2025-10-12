/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:50:19 by asando            #+#    #+#             */
/*   Updated: 2025/10/12 13:51:54 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->fork[i++], NULL))
			return (-1);
	}
	if (pthread_mutex_init(data->mutex_print, NULL))
		return (-1);
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].n_eat = 0;
		data->philo[i].right_fork = &data->fork[i];
		data->philo[i].left_fork = &data->fork[(i + 1) % data->n_philo];
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (data->philo == NULL)
		return (-1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (data->fork == NULL)
		return (-1);
	if (init_mutex(data) == -1)
		return (-1);
	if (init_philo(data) == -1)
		return (-1);
	data->time_start_ms = get_time_ms();
	while (i < data->n_philo)
	{
		data->philo[i].time_last_eat_ms = get_time_ms();
		if (pthread_create(data->philo[i].thread, NULL, action,
					 (void *)(&data->philo[i]))
			return (-1);
		i++;
	}
	return (0);
}
