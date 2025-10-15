/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:27:39 by asando            #+#    #+#             */
/*   Updated: 2025/10/14 20:44:14 by asando           ###   ########.fr       */
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

long	get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	ft_usleep(long target_time_ms, t_data *data)
{
	long start;

	start = get_time_ms();
	while (1)
	{
		if (get_time_ms() - start >= target_time_ms || data->end_simulation == true)
			break ;
		usleep(5);
	}
	return ;
}
