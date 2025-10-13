/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:50:19 by asando            #+#    #+#             */
/*   Updated: 2025/10/13 14:10:19 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->fork[i++]), NULL))
			return (-1);
	}
	if (pthread_mutex_init(&(data->mutex_print), NULL))
		return (-1);
	return (0);
}

static int	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while(i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].n_eat = 0;
		philo[i].right_fork = &data->fork[i];
		philo[i].left_fork = &data->fork[(i + 1) % data->n_philo];
		philo[i].data = data;
		i++;
	}
	return (0);
}

static int	create_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->time_start_ms = get_time_ms();
	while (i < data->n_philo)
	{
		(philo + i)->time_last_eat_ms = get_time_ms();
		if (pthread_create(&((philo + i)->thread), NULL, philo_action,
					 (void *)(philo + i)))
			return (-1);
		i++;
	}
	return (0);
}

int	init_thread(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * data->n_philo);
	if (*philo == NULL)
		return (-1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (data->fork == NULL)
		return (-1);
	if (init_mutex(data) == -1)
	{
		free(*philo);
		free(data->fork);
		return (-1);
	}
	init_philo(data, *philo);
	if (create_thread(data, *philo) == -1)
	{
		free(*philo);
		free(data->fork);
		return (-1);
	}
	return (0);
}
