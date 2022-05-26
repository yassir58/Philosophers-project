/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:56 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 13:20:13 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct data_s
{
	long			philo_count;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			time_to_die;
	long			start_time;
	int				philo_died;
	pthread_mutex_t	print_lock;
	int				philos_eat_count;
	int				all_eaten;
}	t_data;

typedef struct fork_s
{
	pthread_mutex_t	lock;
	int				fork_number;
}	t_fork;

typedef struct philo_s
{
	int		philo_id;
	int		eat_count;
	long	death_timer;
	t_fork	*left_fork;
	t_fork	*right_fork;
	t_data	*data;
}	t_philo;

t_data	*init_data(int argc, char *argv[]);
void	cleaner_function(pthread_t *threads, t_philo *philos, t_data *data,
			t_fork *forks);
void	create_threads(int count, pthread_t *threads,
			void *(thread_function)(void *), t_philo *philos);
t_fork	*init_forks(int count);
t_philo	*init_philos(int count, t_fork *forks, t_data *data);
int		get_right_indx(t_philo *philo);
int		get_left_indx(t_philo *philo);
long	get_milliseconds(void);
long	get_timestamp(long time_ref);
void	start_eating(t_philo *philo);
void	start_sleeping(t_philo *philo);
void	start_thinking(t_philo *philo);
void	schedule_philo(t_philo *philos);
int		right_fork_available(t_philo *philo);
int		left_fork_available(t_philo *philo);
void	handle_philo_died(t_philo *philo);
int		validate_args(int argc, char *argv[]);
long	ft_latoi(const char *str);
int		ft_isdigit(int c);
int		check_philo_death(t_data *data, t_philo *philo_state);
int		check_philo_eat_count(t_data *data);
void	args_err(void);
void	*philo_routine(void *arg);
void	print_status(t_philo *philo, char *message, int status);
void	ft_usleep(long time);
int		is_number(char *str);
#endif