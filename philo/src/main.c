/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:42:31 by asando            #+#    #+#             */
/*   Updated: 2025/11/28 14:41:20 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&(data->fork[i++]));
	pthread_mutex_destroy(&(data->mutex_print_log));
	return ;
}

void	ft_join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_join(data->philo[i++].thread, NULL);
	return ;
}

static int	ft_start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->time_start_ms = ft_get_time_ms() + (10 * data->n_philo);
	while (i < data->n_philo)
	{
		philo[i].time_last_eat_ms = data->time_start_ms;
		if (pthread_create(&(philo[i].thread), NULL, ft_philo_action,
				(void *)(&philo[i])))
		{
			ft_system_failed(THREAD_FAIL, "philo->thread");
			while (--i >= 0)
				pthread_join(philo[i].thread, NULL);
			ft_destroy_mutex(data);
			return (-1);
		}
		i++;
	}
	if (ft_start_monitoring_thread(data))
	{
		ft_join_thread(data);
		return (-1);
	}
	return (0);
}

static void	ft_stop_simulation(t_data *data)
{
	ft_join_thread(data);
	if (data->n_philo > 1)
		pthread_join(data->monitor_thread, NULL);
	ft_destroy_mutex(data);
	if (data->n_philo > 1)
	{
		pthread_mutex_destroy(&(data->mutex_monitor_simulation_status));
		pthread_mutex_destroy(&(data->mutex_monitor_last_eat_time));
		pthread_mutex_destroy(&(data->mutex_monitor_n_eat));
	}
	return ;
}

// NOTE: Usage ./philo 4 410 200 200 || ./philo 4 410 200 200 5

/*  BUG: Fail case 1 800 200 200 doesnt show any thread running should die
 *  it wait mutex for fork
 *  TODO: Create action for one philo only
 *  NOTE: for one Philo case, ft_start_monitor_thread should not run
*/

/* BUG: Failed case 5 800 200 200 7 when it times to finish it doesnt
 * show enough eating log
 * TODO: Check on ft_all_eat_enough
 * TODO: Check for logging on ft_action
*/
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (ft_parse_input(argc, argv, &data) == -1)
		return (-1);
	if (ft_init_simulation(&data, &philo) == -1)
	{
		ft_free_alloc(&philo, &data);
		return (-1);
	}
	if (ft_start_simulation(&data, philo) == -1)
	{
		ft_free_alloc(&philo, &data);
		return (-1);
	}
	ft_stop_simulation(&data);
	ft_free_alloc(&philo, &data);
	return (0);
}
