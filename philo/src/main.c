/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:42:31 by asando            #+#    #+#             */
/*   Updated: 2025/10/26 14:42:34 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&(data->fork[i++]));
	pthread_mutex_destroy(&(data->mutex_print));
}

// TODO: Create modular function, so in main there is no int i variable
// TODO: Create Stop_thread function
// TODO: Before closing need to destroy all mutex
// TEST: for 1 philo
// TEST: when simulation reach n_max
// TEST: n_eat_max == 0, and n_philo < 1
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	philo = NULL;
	if (parse_input(argc, argv, &data) == -1)
		return (-1);
	if (init_thread(&data, &philo) == -1)
		return (-1);
	while (i < data.n_philo)
		pthread_join(philo[i++].thread, NULL);
	destroy_mutex(&data);
	free(philo);
	free(data.fork);
	return (0);
}
