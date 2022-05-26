/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:58:51 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 15:22:34 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_function(void *arg)
{
	t_data	*data;
	long	diff;

	data = (t_data *)arg;
	while (1)
	{
		diff = get_milliseconds () - ft_mls (data->death_timer);
		if (diff >= data->time_to_die && !data->busy)
		{
			if (data->philo_count != 1)
				sem_wait (data->turn);
			print_status (data, "died");
			kill_zombies (data);
			exit (EXIT_FAILURE);
		}
	}
	return (NULL);
}

void	death_monitor(t_data *data, pthread_t thread, int *flag)
{
	(*flag)++;
	pthread_create (&thread, NULL, &monitor_function, data);
	pthread_detach (thread);
}

void	philo_routine(t_data *data, sem_t *left, sem_t *right)
{
	pthread_t	thread;
	int			flag;

	thread = NULL;
	flag = 0;
	gettimeofday (&data->start_time, NULL);
	gettimeofday (&data->death_timer, NULL);
	if (data->phid % 2 != 0 && data->philo_count != 1)
		ft_usleep (data->time_to_eat - 10);
	while (1)
	{
		if (flag == 0)
			death_monitor (data, thread, &flag);
		get_forks (data, left, right);
		philo_eating (data, left, right);
		if (data->eat_count == data->must_eat)
			break ;
		philo_sleeping (data);
		philo_thinking (data);
	}
	exit (EXIT_SUCCESS);
}

void	start_simulation(t_data *data, sem_t **forks)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		create_process (data, i, forks);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	sem_t	**forks;

	data = NULL;
	if (argc < 5 || argc > 6 || !validate_args (argc, argv))
		invalid_arguments ();
	data = init (data, argc, argv);
	forks = init_forks (data);
	data->wait = init_wait_sem (data);
	start_simulation (data, forks);
	if (data->id == 0)
		philo_routine (data, forks[data->phid - 1],
			forks[get_right_indx (data)]);
	else if (data->id != 0)
	{
		wait_for_children (data);
		cleaner_function (data, forks);
	}
	return (0);
}
