/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:55:20 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/06/08 12:28:31 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		|| args->t_to_die < 60 || args->t_to_eat < 60 || args->t_to_sleep < 60
		|| args->nbr_of_t_each_philo_must_eat == 0)
		return (1);
	return (0);
}

int	creat_philo(t_thread *args, t_philo *philo)
{
	int	i;

	i = 0;
	args->start_time = ft_time(0);
	args->status = 0;
	args->fork = malloc((sizeof(pthread_mutex_t) * args->nbr_of_philo));
	if (!args->fork)
		return (1);
	while (i < args->nbr_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].info = args;
		philo[i].nbr_eat = 0;
		pthread_mutex_init(&args->fork[i], NULL);
		pthread_mutex_init(&philo[i].eat, NULL);
		philo[i].lst_eat = ft_time(philo->info->start_time);
		i++;
	}
	pthread_mutex_init(&philo->info->print, NULL);
	pthread_mutex_init(&philo->info->death, NULL);
	return (0);
}

int	creat_tread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nbr_of_philo)
	{
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		usleep(60);
		i += 2;
	}
	i = 1;
	while (i < philo->info->nbr_of_philo)
	{
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		usleep(60);
		i += 2;
	}
	is_died(philo);
	i = -1;
	while (++i < philo->info->nbr_of_philo)
		pthread_join(philo[i].philo, NULL);
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
		{
			free(philo);
			return (1);
		}
		if (creat_tread(philo))
		{
			free_all(philo);
			return (1);
		}
		free_all(philo);
	}
}
