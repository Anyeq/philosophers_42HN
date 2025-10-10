/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:47:04 by asando            #+#    #+#             */
/*   Updated: 2025/10/10 14:54:21 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_input(argc, argv, &data) == -1)
		return (-1);
	printf("%d\n", data.n_philo);
	printf("%d\n", data.time_to_die);
	printf("%d\n", data.time_to_eat);
	printf("%d\n", data.time_to_sleep);
	return (0);
}
