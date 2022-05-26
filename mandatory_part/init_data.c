/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:00:13 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 13:16:12 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

t_data	*init_data(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = 1;
	data = (t_data *) malloc (sizeof (t_data));
	if (!data)
		return (NULL);
	data->philo_died = 1;
	data->start_time = get_milliseconds ();
	data->philo_count = ft_latoi (argv[i++]);
	data->time_to_die = ft_latoi (argv[i++]);
	data->time_to_eat = ft_latoi (argv [i++]);
	data->time_to_sleep = ft_latoi (argv[i++]);
	if (argc == 6)
		data->must_eat = atoi (argv[i]);
	else
		data->must_eat = -1;
	return (data);
}

void	cleaner_function(pthread_t *threads, t_philo *philos, t_data *data,
t_fork *forks)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy (&(forks[i].lock));
		i++;
	}
	free (data);
	free (forks);
	free (philos);
	free (threads);
}

void	create_threads(int count, pthread_t *threads,
void *(thread_function)(void*), t_philo *philos)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_create (&(threads[i]), NULL, thread_function, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < count)
	{
		pthread_detach (threads[i]);
		i++;
	}
}

t_fork	*init_forks(int count)
{
	t_fork	*forks_state;
	int		i;

	i = 0;
	forks_state = (t_fork *)malloc (sizeof (t_fork) * count);
	if (!forks_state)
		return (NULL);
	while (i < count)
	{
		forks_state[i].fork_number = i + 1;
		pthread_mutex_init (&(forks_state[i].lock), NULL);
		i++;
	}
	return (forks_state);
}

t_philo	*init_philos(int count, t_fork *forks, t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *) malloc (sizeof (t_philo) * count);
	if (!philos)
		return (NULL);
	while (i < count)
	{
		philos[i].data = data;
		philos[i].eat_count = 0;
		philos[i].philo_id = i + 1;
		philos[i].left_fork = &forks[get_left_indx (&philos[i])];
		philos[i].right_fork = &forks[get_right_indx (&philos[i])];
		philos[i].death_timer = data->start_time;
		i++;
	}
	return (philos);
}
