/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:42:59 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 15:12:23 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(long time)
{
	long	start;

	start = get_milliseconds();
	while ((get_milliseconds() - start) < time)
		usleep(20);
}

t_data	*init_data(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = 1;
	data = (t_data *) malloc (sizeof (t_data));
	if (!data)
		return (NULL);
	data->philo_count = ft_latoi (argv[i++]);
	data->time_to_die = ft_latoi (argv[i++]);
	data->time_to_eat = ft_latoi (argv [i++]);
	data->time_to_sleep = ft_latoi (argv[i++]);
	data->eat_count = 0;
	data->thinking = 1;
	gettimeofday (&data->start_time, NULL);
	gettimeofday (&data->death_timer, NULL);
	data->busy = 0;
	data->pids = malloc (sizeof (int) * data->philo_count);
	if (argc == 6)
		data->must_eat = atoi (argv[i]);
	else
		data->must_eat = -1;
	return (data);
}

void	handle_error(t_data *data, sem_t **forks)
{
	int		i;
	char	*sem_name;

	i = 0;
	while (i < data->philo_count)
	{
		sem_name = ft_itoa (i);
		sem_unlink (sem_name);
		sem_close (forks[i]);
		free (sem_name);
		i++;
	}
	free (data);
	free (forks);
	printf ("Error \n");
	exit (EXIT_FAILURE);
}

sem_t	*init_fork(int id, int value)
{
	char	*sem_name;
	sem_t	*sem;

	sem = NULL;
	sem_name = ft_strjoin ("fork_", ft_itoa(id));
	sem_unlink (sem_name);
	sem = sem_open (sem_name, O_CREAT, 0644, value);
	free (sem_name);
	if (sem == SEM_FAILED)
		write (2, "SEM_FAILED\n", 11);
	return (sem);
}

void	cleaner_function(t_data *data, sem_t **forks)
{
	int		i;
	char	*sem_name;
	char	*wait_name;

	i = 0;
	while (i < data->philo_count)
	{
		sem_close (forks[i]);
		sem_close (data->wait[i]);
		sem_name = ft_strjoin ("fork_", ft_itoa (i));
		wait_name = ft_strjoin ("wait_sem", ft_itoa (i));
		sem_unlink (sem_name);
		sem_unlink (wait_name);
		free (sem_name);
		free (wait_name);
		i++;
	}
	sem_unlink ("start_sem");
	sem_unlink ("turn_sem");
	sem_close (data->turn);
	sem_close (data->start);
	free (forks);
	free (data);
}
