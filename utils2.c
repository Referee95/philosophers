/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:23:28 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/06/08 13:33:07 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->info->nbr_of_philo)
	{
		pthread_mutex_destroy(&philo[i].eat);
		pthread_mutex_destroy(&philo->info->fork[i]);
	}
	pthread_mutex_destroy(&philo->info->print);
	pthread_mutex_destroy(&philo->info->death);
	free(philo->info->fork);
	free(philo);
}

long	read_valu(long *value, pthread_mutex_t *mtx)
{
	long	retur;

	pthread_mutex_lock(mtx);
	retur = *value;
	pthread_mutex_unlock(mtx);
	return (retur);
}

void	ft_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death);
	philo->info->status = 1;
	pthread_mutex_unlock(&philo->info->death);
}

int	philo_satiation(t_philo *philo)
{
	int	i;
	int	don;

	i = 0;
	don = 1;
	if (philo->info->nbr_of_t_each_philo_must_eat == -1)
		return (0);
	while (i < philo->info->nbr_of_philo)
	{
		if (read_valu(&philo[i].nbr_eat,
				&philo[i].eat) < philo->info->nbr_of_t_each_philo_must_eat)
			don = 0;
		i++;
	}
	if (don)
	{
		pthread_mutex_lock(&philo->info->death);
		philo->info->status = 1;
		pthread_mutex_unlock(&philo->info->death);
		return (1);
	}
	return (0);
}

int	is_died(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < philo->info->nbr_of_philo)
		{
			if ((ft_time(philo->info->start_time) - read_valu(&philo[i].lst_eat,
						&philo[i].eat)) >= philo->info->t_to_die)
			{
				ft_status(philo);
				pthread_mutex_lock(&philo->info->print);
				printf("%ld %d died\n", ft_time(philo->info->start_time),
					philo[i].id);
				if (philo->info->nbr_of_philo == 1)
					pthread_mutex_unlock(&philo->info->fork[0]);
				pthread_mutex_unlock(&philo->info->print);
				return (1);
			}
			if (philo_satiation(philo))
				return (1);
		}
	}
	return (0);
}
