/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:46:09 by yelatman          #+#    #+#             */
/*   Updated: 2022/05/25 14:52:18 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_itoa(int num)
{
	char	*res;
	int		i;
	int		temp;

	i = 0;
	temp = num;
	while (temp != 0)
	{
		temp /= 10;
		i++;
	}
	res = (char *) malloc (sizeof (char) * (i + 1));
	if (!res)
		return (NULL);
	res[i] = 0;
	while (num != 0)
	{
		res[--i] = (num % 10) + 48;
		num /= 10;
	}
	return (res);
}

void	philo_sleeping(t_data *data)
{
	print_status (data, "is sleeping");
	ft_usleep (data->time_to_sleep);
}

t_data	*init(t_data *data, int argc, char *argv[])
{
	data = init_data (argc, argv);
	data->id = MAX_INT;
	sem_unlink ("start_sem");
	sem_unlink ("turn_sem");
	data->start = sem_open ("start_sem", O_CREAT, 0644, 1);
	data->turn = sem_open ("turn_sem", O_CREAT, 0644, 1);
	if (data->start == SEM_FAILED || data->turn == SEM_FAILED)
		printf ("SEM_FAILED \n");
	return (data);
}

sem_t	**init_wait_sem(t_data *data)
{
	char	*name;
	sem_t	**sem;
	int		i;

	i = 0;
	sem = malloc (sizeof (sem_t *) * data->philo_count);
	if (!sem)
		return (NULL);
	while (i < data->philo_count)
	{
		name = ft_strjoin ("wait_sem", ft_itoa(i + 1));
		sem_unlink (name);
		sem[i] = sem_open (name, O_CREAT, 0644, 0);
		free (name);
		if (sem[i] == SEM_FAILED)
		{
			write (2, "SEM_FAILED\n", 11);
			return (NULL);
		}
		i++;
	}
	return (sem);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len) + 1);
	if (str != 0)
	{
		while (s1[++i] != 0)
			str[i] = s1[i];
		j = i;
		i = 0;
		while (s2[i] != 0)
			str[j++] = s2[i++];
		str[j] = 0;
		return (str);
	}
	return (0);
}
