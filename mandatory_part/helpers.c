/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:00:03 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 13:15:31 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	get_right_indx(t_philo *philo)
{
	if (philo->philo_id - 1 == 0)
		return ((philo->data->philo_count - 1));
	else if (philo->philo_id - 1 == (philo->data->philo_count - 1))
		return ((philo->data->philo_count - 2));
	else
		return (((philo->philo_id - 1) - 1));
}

int	get_left_indx(t_philo *philo)
{
	return (philo->philo_id - 1);
}

int	check_philo_death(t_data *data, t_philo *philo_state)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (get_milliseconds() - philo_state[i].death_timer
			>= data->time_to_die)
		{
			print_status (&philo_state[i], "died", 0);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_philo_eat_count(t_data *data)
{
	if (data->philos_eat_count == data->philo_count)
		return (0);
	return (1);
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
