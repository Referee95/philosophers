/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:12:29 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/06/08 13:23:45 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (read_valu(&philo->info->status, &philo->info->death))
			return (NULL);
		philo_think(philo);
		res_fork(philo);
		philo_eating(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_sleep(t_philo *philo)
{
	ft_print("is sleeping", philo);
	my_sleep(philo->info->t_to_sleep, philo);
	pthread_mutex_lock(&philo->eat);
	philo->nbr_eat++;
	pthread_mutex_unlock(&philo->eat);
}

void	philo_eating(t_philo *philo)
{
	int	fork_prime;

	fork_prime = philo->id - 1;
	pthread_mutex_lock(&philo->eat);
	ft_print("is eating", philo);
	philo->lst_eat = ft_time(philo->info->start_time);
	pthread_mutex_unlock(&philo->eat);
	my_sleep(philo->info->t_to_eat, philo);
	pthread_mutex_unlock(&philo->info->fork[fork_prime]);
	pthread_mutex_unlock(&philo->info->fork[philo->id
		% philo->info->nbr_of_philo]);
}

void	res_fork(t_philo *philo)
{
	int	fork_prime;

	fork_prime = philo->id - 1;
	pthread_mutex_lock(&philo->info->fork[fork_prime]);
	ft_print("has taken a fork", philo);
	pthread_mutex_lock(&philo->info->fork[philo->id
		% philo->info->nbr_of_philo]);
	ft_print("has taken a fork", philo);
}

void	philo_think(t_philo *philo)
{
	ft_print("is thinking", philo);
}
