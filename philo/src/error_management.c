/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:39:27 by asando            #+#    #+#             */
/*   Updated: 2025/12/13 09:25:22 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usage(t_input_flag flag)
{
	if (flag & INVALID_NPARAMS)
	{
		printf("INVALID_NPARAMS!\n");
		printf("Usage philo <number_of_philosophers> "
			" <time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_time_each_philosophers_need_to_eat]");
	}
	else if (flag & INVALID_NPHILO)
		printf("INVALID_NPHILO!\nnumber_of_philosophers couldn't less than 1");
	else
		printf("INVALID_TIME!\nparameter has to be more than 0");
	return ;
}

void	ft_system_failed(t_fail_flag flag, char *str)
{
	if (flag & MALLOC_FAIL)
		printf("Error: malloc on %s failed", str);
	else if (flag & MUTEX_FAIL)
		printf("Error: pthread_mutex_init on %s failed", str);
	else
		printf("Error: pthread_create on %s failed", str);
	return ;
}

void	ft_free_alloc(t_philo **philo, t_data *data)
{
	free(*philo);
	free(data->fork);
	*philo = NULL;
	data->fork = NULL;
	data->philo = NULL;
	return ;
}
