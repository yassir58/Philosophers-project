/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:41:22 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 14:28:40 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_right_indx(t_data *data)
{
	if (data->phid - 1 == 0)
		return ((data->philo_count - 1));
	else if (data->phid - 1 == (data->philo_count - 1))
		return ((data->philo_count - 2));
	else
		return (((data->phid - 1) - 1));
}

int	get_left_indx(t_data *data)
{
	return (data->phid - 1);
}

sem_t	**init_forks(t_data *data)
{
	int				i;
	unsigned int	value;
	sem_t			**forks;

	i = 0;
	value = 1;
	forks = malloc (sizeof (sem_t *) * data->philo_count);
	if (!forks)
		return (NULL);
	while (i < data->philo_count)
	{
		forks[i] = init_fork (i, value);
		if (!forks[i])
			handle_error (data, forks);
		i++;
	}
	return (forks);
}

void	philo_eating(t_data *data, sem_t *left, sem_t *right)
{
	print_status (data, "is eating");
	gettimeofday (&data->death_timer, NULL);
	data->eat_count++;
	ft_usleep (data->time_to_eat);
	sem_post (left);
	sem_post (right);
	data->busy = 0;
}

void	wait_for_children(t_data *data)
{
	int	i;
	int	status;
	int	rt;

	i = 0;
	rt = 1;
	while (rt > 0)
	{
		rt = waitpid (data->pids[i], &status, 0);
		if (WIFEXITED (status))
		{
			if (WEXITSTATUS (status))
			{
				printf ("EXIT_FAILED \n");
				kill_zombies (data);
				exit (0);
			}
		}
		i++;
	}
}
