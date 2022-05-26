/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:49:27 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 13:51:02 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_milliseconds(void)
{
	struct timeval	time_stamp;

	gettimeofday (&time_stamp, NULL);
	return ((time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000));
}

long	get_timestamp(long time_ref)
{
	return (get_milliseconds () - time_ref);
}

long	ft_latoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			||str[i] == '\f' || str[i] == '\r') && str[i] != '\0')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	validate_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_latoi (argv[i]) > MAX_INT || ft_latoi (argv[i]) < 0
			|| !is_number (argv[i]))
			return (0);
		i++;
	}
	return (1);
}
