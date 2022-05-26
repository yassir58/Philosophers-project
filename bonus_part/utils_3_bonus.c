/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:47:46 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 15:13:33 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	get_forks(t_data *data, sem_t *left, sem_t *right)
{
	sem_wait (data->turn);
	sem_wait (left);
	print_status (data, "has taken a fork");
	sem_wait (right);
	print_status (data, "has taken a fork");
	data->busy = 1;
	sem_post (data->turn);
}

void	philo_thinking(t_data *data)
{
	print_status (data, "is thinking");
	data->thinking = 0;
}

void	args_err(t_data *data)
{
	free (data);
	invalid_arguments ();
}

void	invalid_arguments(void)
{
	write (2, "Invalid arguments\n", 18);
	exit (EXIT_FAILURE);
}
