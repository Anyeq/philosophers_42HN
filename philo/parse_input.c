/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:10:56 by asando            #+#    #+#             */
/*   Updated: 2025/10/07 16:38:50 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usage(void)
{
	printf("Usage philo <number_of_philosophers> " 
			" <time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_time_each_philosophers_need_to_eat]");
}

int	parse_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_usage();
		return (-1);
	}
	
	return (0);
}
