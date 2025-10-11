/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:47:04 by asando            #+#    #+#             */
/*   Updated: 2025/10/11 13:54:34 by asando           ###   ########.fr       */
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

void	*philo_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ()
}

int	init(){}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	philo = NULL;
	if (parse_input(argc, argv, &data) == -1)
		return (-1);
	philo = malloc(sizeof(t_philo) * data.n_philo);
	data.time_start_ms = get_time_ms();
	while (i < data.n_philo)
		pthread_create(philo[i++].thread, NULL, action, NULL);
	i = 0;
	while (i < data.n_philo)
		pthread_join(philo[i++]);
	return (0);
}
