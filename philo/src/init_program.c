/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:50:19 by asando            #+#    #+#             */
/*   Updated: 2026/01/08 16:51:02 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex_eat(t_data *data, int code, int i)
{
	int	iter;

	if (code == 1)
		iter = i;
	else if (code == 2)
		iter = data->n_philo;
	while (code == 1 && --iter >= 0)
		pthread_mutex_destroy(&(data->philo[iter].mutex_n_eat));
	iter = i;
	while (code == 1 && --iter >= 0)
		pthread_mutex_destroy(&(data->philo[iter].mutex_last_eat_time));
	return ;
}

static int	ft_init_mutex_n_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->philo[i].mutex_n_eat), NULL))
		{
			ft_system_failed(MUTEX_FAIL, "philo->mutex_n_eat");
			ft_destroy_mutex_eat(data, 1, i);
			return (-1);
		}
		if (pthread_mutex_init(&(data->philo[i].mutex_last_eat_time), NULL))
		{
			ft_system_failed(MUTEX_FAIL, "philo->mutex_last_eat_time");
			ft_destroy_mutex_eat(data, 2, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
		{
			ft_system_failed(MUTEX_FAIL, "data->fork");
			while (--i >= 0)
				pthread_mutex_destroy(&(data->fork[i]));
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&(data->mutex_print_log), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_print_log");
		while (--i >= 0)
			pthread_mutex_destroy(&(data->fork[i]));
		return (-1);
	}
	if (ft_init_mutex_n_eat(data) != 0)
	{
		ft_destroy_mutex(data);
		return (-1);
	}
	return (0);
}

static int	ft_init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].n_eat = 0;
		if ((i + 1) % 2 == 0)
		{
			philo[i].right_fork = &data->fork[i];
			philo[i].left_fork = &data->fork[(i + 1) % data->n_philo];
		}
		else
		{
			philo[i].left_fork = &data->fork[i];
			philo[i].right_fork = &data->fork[(i + 1) % data->n_philo];
		}
		philo[i].data = data;
		philo[i].has_fork = false;
		i++;
	}
	return (0);
}

int	ft_init_simulation(t_data *data, t_philo **philo)
{
	*philo = malloc(sizeof(t_philo) * data->n_philo);
	if (*philo == NULL)
	{
		ft_system_failed(MALLOC_FAIL, "philo");
		return (-1);
	}
	data->philo = *philo;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (data->fork == NULL)
	{
		ft_system_failed(MALLOC_FAIL, "data->fork");
		return (-1);
	}
	if (ft_init_mutex(data) == -1)
		return (-1);
	if (pthread_mutex_init(&(data->mutex_monitor_simulation_status), NULL))
	{
		ft_system_failed(MUTEX_FAIL, "data->mutex_simulation_status");
		ft_destroy_mutex(data);
		return (-1);
	}
	ft_init_philo(data, *philo);
	return (0);
}
