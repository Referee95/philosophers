/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:55:25 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/05/25 16:01:53 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_thread
{
	int				nbr_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nbr_of_t_each_philo_must_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	long			start_time;
}					t_thread;

typedef struct s_philo
{
	pthread_t		philo;
	t_thread		*info;
	int				id;
	int				nbr_eat;
	long			lst_eat;
}					t_philo;

int					ft_atoi(char *str);
int					ft_check(char **av, int ac, t_thread *args);
int					creat_philo(t_thread *args, t_philo *philo);
int					creat_tread(t_philo *philo);
long				ft_time(long time);
void				my_sleep(long time);
void				*routine(void *arg);
void				res_fork(t_philo *philo);
void				philo_think(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_eating(t_philo *philo);

#endif