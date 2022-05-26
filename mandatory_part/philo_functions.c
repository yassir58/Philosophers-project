/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:00:29 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 13:17:47 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	start_eating(t_philo *philo)
{
	print_status (philo, "is eating", 1);
	philo->death_timer = get_milliseconds ();
	ft_usleep (philo->data->time_to_eat);
	philo->eat_count++;
}

void	start_sleeping(t_philo *philo)
{
	print_status (philo, "is sleeping", 1);
	ft_usleep (philo->data->time_to_sleep);
}

void	start_thinking(t_philo *philo)
{
	print_status (philo, "is thinking", 1);
}

void	args_err(void)
{
	printf ("Error \n");
	exit (1);
}

void	print_status(t_philo *philo, char *message, int status)
{
	pthread_mutex_lock (&philo->data->print_lock);
	printf ("%ld\t\t%d\t%s\n", get_timestamp(philo->data->start_time),
		philo->philo_id, message);
	if (status)
		pthread_mutex_unlock (&philo->data->print_lock);
}
