/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:44:13 by asando            #+#    #+#             */
/*   Updated: 2025/10/26 23:31:07 by asando           ###   ########.fr       */
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

typedef enum e_input_flag
{
	INVALID_NPARAMS = 1 << 0;
	INVALID_NPHILO = 1 << 1;
	INVALID_INPUT = 1 << 2;
} t_input_flag;

typedef enum e_fail_flag
{
	MALLOC_FAIL = 1 << 0;
	MUTEX_FAIL = 1 << 1;
	THREAD_FAIL = 1 << 2;
} t_fail_flag;

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
	pthread_t		super_thread;
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

typedef struct s_super_variable
{
	t_data	*data;
	t_philo	*philo;
}	t_super_variable;

long	get_time_ms(void);
int		parse_input(int argc, char **argv, t_data *data);
int		init_thread(t_data *data, t_philo **philo);
void	*philo_action(void *arg);

//utils
int		ft_isdigit(unsigned char c);
int		ft_atoi(char *str);
long	get_time_ms(void);
void	ft_usleep(long target_time_ms, t_data *data);
#endif
