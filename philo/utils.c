/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:06:19 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/06/07 19:27:26 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long long	n;

	n = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		n = n * 10 + *str - 48;
		if (n > INT_MAX)
			return (-1);
		str++;
	}
	return (n);
}

void	my_sleep(long time, t_philo *philo)
{
	long long	start;

	start = ft_time(0);
	while (1)
	{
		if (read_valu(&philo->info->status, &philo->info->death))
			break ;
		if (ft_time(0) - start >= time)
			break ;
		usleep(85);
	}
}

long	ft_time(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time);
}

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	if (!read_valu(&philo->info->status, &philo->info->death))
		printf("%ld %d %s\n", ft_time(philo->info->start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->info->print);
}
