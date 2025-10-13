/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:47:04 by asando            #+#    #+#             */
/*   Updated: 2025/10/13 12:09:33 by asando           ###   ########.fr       */
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
	// dont forget to clean the fork and philo at anytime when error happen
	// check edge case in input for n_philo < 1 or 1
	// maybe print error more correctly on the case
	// check the action
	// check if the case is only 1 philo
	// need to destroy all mutex before close
	// simulation end when n max reach
	// adjust usleep by creating usleep fnction
	return (0);
}
