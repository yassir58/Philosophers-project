/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:40:47 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 15:06:29 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_process(t_data *data, int indx, sem_t **forks)
{
	if (data->id > 0)
	{
		data->id = fork ();
		data->phid = indx + 1;
		data->pids[indx] = data->id;
	}
	else if (data->id == -1)
		handle_error (data, forks);
}

void	kill_zombies(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		kill (data->pids[i], SIGINT);
		i++;
	}
}

void	print_status(t_data *data, char *message)
{
	sem_wait (data->start);
	printf ("%ld\t\t%d\t%s\n", get_timestamp(ft_mls(data->start_time)), \
			data->phid, message);
	sem_post (data->start);
}

long	ft_mls(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit (str[i]))
			return (0);
		i++;
	}
	return (1);
}
