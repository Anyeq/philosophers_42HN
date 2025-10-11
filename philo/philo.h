/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:57:11 by asando            #+#    #+#             */
/*   Updated: 2025/10/11 13:46:06 by asando           ###   ########.fr       */
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
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat_max;
	bool			end_simulation;
	long			time_start_ms;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*fork;
} t_data;

typedef struct s_philo
{
	int				id;
	int				n_eat;
	long			time_last_eat_ms;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
} t_philo;

int	parse_input(int argc, char **argv, t_data *data);
#endif
