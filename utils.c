/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:06:19 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/05/25 16:00:38 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

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

void	my_sleep(long time)
{
	long	time_now;

	time_now = ft_time(0) + time;
	while (ft_time(0) < time_now)
		usleep(200);
}

long	ft_time(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time);
}
