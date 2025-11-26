/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:27:39 by asando            #+#    #+#             */
/*   Updated: 2025/11/25 22:55:36 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(unsigned char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str && ft_isdigit((unsigned char)*str))
	{
		res = res * 10 + ((*str - '0') * sign);
		str++;
	}
	return (res);
}

long	ft_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	ft_log_action(t_philo *philo, char *action)
{
	bool	simulation_status;
	long	current_time;

	current_time = ft_get_time_ms();
	pthread_mutex_lock(&(philo->data->mutex_monitor_simulation_status));
	simulation_status = philo->data->end_simulation;
	pthread_mutex_unlock(&(philo->data->mutex_monitor_simulation_status));
	if (simulation_status == false)
	{
		pthread_mutex_lock(&(philo->data->mutex_print_log));
		printf("%ld %d %s\n", current_time - philo->data->time_start_ms,
			philo->id, action);
		pthread_mutex_unlock(&(philo->data->mutex_print_log));
	}
	return ;
}

// NOTE: rename to milisecond
void	ft_usleep(long target_time_ms, t_data *data)
{
	long	start;
	bool	simulation_status;

	start = ft_get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&(data->mutex_monitor_simulation_status));
		simulation_status = data->end_simulation;
		pthread_mutex_unlock(&(data->mutex_monitor_simulation_status));
		if (simulation_status)
			break ;
		if (ft_get_time_ms() - start >= target_time_ms)
			break ;
		usleep(50);
	}
	return ;
}
