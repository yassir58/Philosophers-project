/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:21:19 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 15:22:47 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct data_s
{
	long			philo_count;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			time_to_die;
	struct timeval	start_time;
	struct timeval	death_timer;
	int				eat_count;
	pid_t			main_id;
	int				id;
	int				phid;
	int				*pids;
	sem_t			**wait;
	sem_t			*start;
	sem_t			*turn;
	int				busy;
	int				thinking;
}	t_data;

long	ft_latoi(const char *str);
int		ft_isdigit(int c);
t_data	*init_data(int argc, char *argv[]);
void	ft_usleep(long time);
void	philo_routine(t_data *data, sem_t *left, sem_t *right);
long	get_timestamp(long time_ref);
long	get_milliseconds(void);
long	ft_mls(struct timeval time);
sem_t	**init_forks(t_data *data);
char	*ft_itoa(int num);
void	cleaner_function(t_data *data, sem_t **forks);
int		get_right_indx(t_data *data);
void	kill_zombies(t_data *data);
void	wait_for_children(t_data *data);
void	returno_eating(t_data *data);
void	philo_sleeping(t_data *data);
void	*monitor_function(void *arg);
void	create_process(t_data *data, int indx, sem_t **forks);
void	handle_error(t_data *data, sem_t **forks);
t_data	*init(t_data *data, int argc, char *argv[]);
int		get_right_indx(t_data *data);
sem_t	*init_fork(int id, int value);
void	philo_eating(t_data *data, sem_t *left, sem_t *right);
void	return_fork(t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(char const *str);
void	get_forks(t_data *data, sem_t *left, sem_t *right);
void	philo_thinking(t_data *data);
int		validate_args(int argc, char *argv[]);
void	print_status(t_data *data, char *message);
void	args_err(t_data *data);
void	invalid_arguments(void);
sem_t	**init_wait_sem(t_data *data);
void	start_simulation(t_data *data, sem_t **forks);
int		is_number(char *str);
void	death_monitor(t_data *data, pthread_t thread, int *flag);

#endif