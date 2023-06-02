/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:55:20 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/05/25 16:01:29 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	ft_check(char **av, int ac, t_thread *args)
{
	args->nbr_of_philo = ft_atoi(av[1]);
	args->t_to_die = ft_atoi(av[2]);
	args->t_to_eat = ft_atoi(av[3]);
	args->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		args->nbr_of_t_each_philo_must_eat = ft_atoi(av[5]);
		if (args->nbr_of_t_each_philo_must_eat < 0)
			return (1);
	}
	else
		args->nbr_of_t_each_philo_must_eat = -1;
	if (args->nbr_of_philo <= 0 || args->nbr_of_philo > 200
		|| args->t_to_die < 60 || args->t_to_eat < 60 || args->t_to_sleep < 60)
		return (1);
	return (0);
}


int	creat_philo(t_thread *args, t_philo *philo)
{
	int	i;

	i = 0;
	args->start_time = ft_time(0);
	args->fork = malloc((sizeof(pthread_mutex_t) * args->nbr_of_philo));
	if (!args->fork)
		return (1);
	while (i < args->nbr_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].info = args;
		philo[i].nbr_eat = 0;
		pthread_mutex_init(&args->fork[i], NULL);
		philo[i].lst_eat = args->start_time;
		i++;
	}
	return (0);
}

void	res_fork(t_philo *philo)
{
	int	fortch;

	fortch = philo->id - 1;
	pthread_mutex_lock(&philo->info->fork[fortch]);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d has taken a fork\n", ft_time(philo->info->start_time),
		philo->id);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(&philo->info->fork[philo->id
		% philo->info->nbr_of_philo]);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d has taken a fork\n", ft_time(philo->info->start_time),
		philo->id);
	pthread_mutex_unlock(&philo->info->print);
}

void	philo_eating(t_philo *philo)
{
	int	fortch;

	fortch = philo->id - 1;
	philo->lst_eat = ft_time(philo->info->start_time);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d is eating\n", ft_time(philo->info->start_time), philo->id);
	pthread_mutex_unlock(&philo->info->print);
	my_sleep(philo->info->t_to_eat);
	philo->lst_eat = ft_time(philo->info->start_time);
	philo->nbr_eat++;
	pthread_mutex_unlock(&philo->info->fork[fortch]);
	pthread_mutex_unlock(&philo->info->fork[philo->id
		% philo->info->nbr_of_philo]);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d is sleeping\n", ft_time(philo->info->start_time), philo->id);
	pthread_mutex_unlock(&philo->info->print);
	my_sleep(philo->info->t_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d is thinking\n", ft_time(philo->info->start_time), philo->id);
	pthread_mutex_unlock(&philo->info->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_think(philo);
		res_fork(philo);
		philo_eating(philo);
		philo_sleep(philo);
		if((ft_time(philo->info->start_time) - philo->lst_eat) < philo->info->t_to_die || philo->nbr_eat == philo->info->nbr_of_t_each_philo_must_eat)
		{	
			printf("%ld %d died\n", ft_time(philo->info->start_time), philo->id);
			exit(1);
		}
	}
}

int	creat_tread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nbr_of_philo)
	{
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		i += 2;
		usleep(60);
	}
	i = 1;
	while (i < philo->info->nbr_of_philo)
	{
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		i += 2;
		usleep(60);
	}
	i = 0;
	while (i < philo->info->nbr_of_philo)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_thread	args;

	if (ac == 5 || ac == 6)
	{
		if (ft_check(av, ac, &args))
			return (1);
		philo = malloc(sizeof(t_philo) * args.nbr_of_philo);
		if (!philo)
			return (1);
		if (creat_philo(&args, philo))
			return (1);
		if (creat_tread(philo))
			return (1);
	}
}
