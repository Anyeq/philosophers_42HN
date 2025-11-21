/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:44:13 by asando            #+#    #+#             */
/*   Updated: 2025/11/21 19:51:48 by asando           ###   ########.fr       */
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
	t_philo			*philo;
	pthread_t		monitor_thread;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_sim;
	pthread_mutex_t	mutex_time_check;
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

// Flag for ft_usage function
typedef enum e_input_flag
{
	INVALID_NPARAMS = 1 << 0;
	INVALID_NPHILO = 1 << 1;
	INVALID_INPUT = 1 << 2;
} t_input_flag;

// Flag for ft_system_failed
typedef enum e_fail_flag
{
	MALLOC_FAIL = 1 << 0;
	MUTEX_FAIL = 1 << 1;
	THREAD_FAIL = 1 << 2;
} t_fail_flag;

// Parsing user input function
int		ft_parse_input(int argc, char **argv, t_data *data);

// Error management Function
void	ft_system_failed(t_fail_flag flag, char *str);
void	ft_free_alloc(t_philo **philo, t_data *data);
void	ft_usage(t_input_flag flag);

// Thread initialization Function
int		ft_init_thread(t_data *data, t_philo **philo);
void	*philo_action(void *arg);

// Utils Function
int		ft_isdigit(unsigned char c);
int		ft_atoi(char *str);
void	ft_usleep(long target_time_ms, t_data *data);
void	ft_log_action(t_philo *philo, char *action);
long	ft_get_time_ms(void);
#endif
