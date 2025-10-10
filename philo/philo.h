/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:57:11 by asando            #+#    #+#             */
/*   Updated: 2025/10/10 20:07:35 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_to_eat;
	bool	someone_died;
	long	time_start_ms;
} t_data;

typedef struct s_philo
{
	int			id;
	int			n_eat;
	pthread_t	thread;
} t_philo;

int	parse_input(int argc, char **argv, t_data *data);
#endif
