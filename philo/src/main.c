/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:42:31 by asando            #+#    #+#             */
/*   Updated: 2025/10/27 13:05:23 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&(data->fork[i++]));
	pthread_mutex_destroy(&(data->mutex_print));
	return ;
}

static void	ft_join_thread(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_philo)
		pthread_join(data->philo[i++].thread, NULL);
	if (data->n_philo > 1)
		pthread_join(data->super_thread, NULL);
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (ft_parse_input(argc, argv, &data) == -1)
		return (-1);
	if (init_thread(&data, &philo) == -1)
	{
		ft_free_alloc(&philo, &data);
		return (-1);
	}
	ft_join_thread(&data);
	ft_destroy_mutex(&data);
	ft_free_alloc(&philo, &data);
	return (0);
}
