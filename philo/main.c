/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:47:04 by asando            #+#    #+#             */
/*   Updated: 2025/10/11 20:48:26 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	log_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->data->mutex_print);
	if (philo->data->end_simulation == false)
		printf("%ld %d %s\n", get_time_ms() - philo->data->time_start_ms,
		 philo->data->id, action);
	pthread_mutex_unlock(philo->data->mutex_print);
}


int	init_mutex(t_data *data)
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

ini	init_philo(t_data *data)
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

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (parse_input(argc, argv, &data) == -1)
		return (-1);
	if (init(&data) == -1)
		return (-1);
	while (i < data.n_philo)
		pthread_join(philo[i++], NULL);
	return (0);
}
