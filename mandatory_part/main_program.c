/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:00:22 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 13:18:20 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	ft_usleep(long time)
{
	long	start;

	start = get_milliseconds();
	while ((get_milliseconds() - start) < time)
		usleep(50);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		usleep (philo->data->time_to_eat);
	while (1)
	{
		pthread_mutex_lock (&(philo->left_fork->lock));
		print_status (philo, "has taken a fork", 1);
		pthread_mutex_lock (&(philo->right_fork->lock));
		print_status (philo, "has taken a fork", 1);
		start_eating(philo);
		pthread_mutex_unlock (&(philo->right_fork->lock));
		pthread_mutex_unlock (&(philo->left_fork->lock));
		if (philo->eat_count == philo->data->must_eat)
			break ;
		start_sleeping(philo);
		start_thinking (philo);
	}
	philo->data->philos_eat_count++;
	return (NULL);
}

void	start_simulation(t_data *data, t_philo *philos, pthread_t *threads)
{
	create_threads (data->philo_count, threads, &philo_routine, philos);
	while (data->philo_died)
	{
		data->all_eaten = check_philo_eat_count (data);
		if (!data->all_eaten)
			break ;
		data->philo_died = check_philo_death (data, philos);
	}
}

int	main(int argc, char *argv[])
{
	t_philo		*philo_state;
	t_fork		*fork_state;
	pthread_t	*threads;
	t_data		*data;

	if (argc < 5 || argc > 6)
		return (0);
	if (!validate_args (argc, argv))
		args_err ();
	data = init_data (argc, argv);
	threads = (pthread_t *) malloc (sizeof (pthread_t) * (data->philo_count));
	if (!threads)
		return (0);
	fork_state = init_forks (data->philo_count);
	philo_state = init_philos (data->philo_count, fork_state, data);
	start_simulation (data, philo_state, threads);
	cleaner_function (threads, philo_state, data, fork_state);
}
